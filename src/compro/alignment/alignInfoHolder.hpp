#pragma once
/*
 *
 *
 *  Created on: Jun 25, 2014
 *      Author: nickhathaway <nickjhathaway@gmail.com>
 */
#include "compro/common.h"
#include "compro/alignment/substitutionMatrix.hpp"
#include "compro/alignment/alignerUtils.hpp"
#include "compro/utils.h"
namespace compro {
struct gapInfo {

  gapInfo() : pos_(0), size_(0) {}
  gapInfo(uint32_t pos, uint32_t size, bool gapInA)
      : pos_(pos), size_(size), gapInA_(gapInA) {}

  // member
  uint32_t pos_;
  uint32_t size_;
  bool gapInA_;
  void writeInfo(std::ostream& out) const {
    out << pos_ << "," << size_ << "," << gapInA_ << std::endl;
  }
  void writeInfoNoEnd(std::ostream& out) const {
    out << pos_ << "," << size_ << "," << gapInA_;
  }
  bool operator>(const gapInfo& otherInfo) const {
    return pos_ > otherInfo.pos_;
  }
  bool operator<(const gapInfo& otherInfo) const {
    return pos_ < otherInfo.pos_;
  }
  bool operator==(const gapInfo& otherInfo) const {
    return (pos_ == otherInfo.pos_ && size_ == otherInfo.size_ &&
            gapInA_ == otherInfo.gapInA_);
  }
  bool operator<=(const gapInfo& otherInfo) const {
    return pos_ <= otherInfo.pos_;
  }
  bool operator>=(const gapInfo& otherInfo) const {
    return pos_ >= otherInfo.pos_;
  }
  virtual void printDescription(std::ostream& out, bool deep) const {
    out << "gapInfo{" << std::endl << "pos_:" << pos_ << std::endl
        << "size_:" << size_ << std::endl << "gapInA_:" << gapInA_ << std::endl;
    out << "}" << std::endl;
  }
};
struct alnInfoLocal {
  // Constructors
  // empty constructor
  alnInfoLocal()
      : localAStart_(0),
        localASize_(0),
        localBStart_(0),
        localBSize_(0),
        score_(0),
        addFromFile_(false)
         {}
  // constructor for local alignment
  alnInfoLocal(const std::vector<gapInfo>& gInfos, uint32_t localAStart,
               uint32_t localASize, uint32_t localBStart, uint32_t localBSize,
               double score, bool addFromFile)
      : gapInfos_(gInfos),
        localAStart_(localAStart),
        localASize_(localASize),
        localBStart_(localBStart),
        localBSize_(localBSize),
        score_(score),
        addFromFile_(addFromFile) {}

  // members
  std::vector<gapInfo> gapInfos_;
  uint32_t localAStart_;
  uint32_t localASize_;
  uint32_t localBStart_;
  uint32_t localBSize_;
  double score_;
  bool addFromFile_;


  // functions
  static alnInfoLocal readInfo(std::stringstream& ss,
                std::vector<std::string>& info,
                std::vector<std::string>& inputGapInfo,
                std::vector<gapInfo> & gInfos,
                std::string & out);
  //
  void writeInfoSingleLine(std::ostream& indexFile,
  												 uint64_t seq1,
                           uint64_t seq2) const;

  virtual void printDescription(std::ostream& out, bool deep) const {
    out << "localAStart_:" << localAStart_ << std::endl << "localASize_:"
        << localASize_ << std::endl << "localBStart_:" << localBStart_
        << std::endl << "localBSize_:" << localBSize_ << std::endl
        << "score_:" << score_ << std::endl;
    if (deep) {
      out << "gapInfo:" << std::endl;
      out << "std::vector<gapInfo> gapInfos_" << std::endl;
      for (const auto& g : gapInfos_) {
        g.printDescription(out, deep);
      }
    }
    out << "}" << std::endl;
  }
};

struct alnInfoGlobal {
  // contructors
  // empty construcor
  alnInfoGlobal() :score_(0), addFromFile_(false) {}
  // contructor for global alingment
  alnInfoGlobal(const std::vector<gapInfo>& gInfos, double score, bool addFromFile)
      : gapInfos_(gInfos),score_(score), addFromFile_(addFromFile) {}

  // members
  std::vector<gapInfo> gapInfos_;
  double score_;
  bool addFromFile_;

  //functions
  static alnInfoGlobal readInfo(std::stringstream& ss,
                std::vector<std::string>& info,
                std::vector<std::string>& inputGapInfo,
                std::vector<gapInfo> & gInfos, std::string & out);

  void writeInfoSingleLine(std::ostream& indexFile,
  												 uint64_t seq1,
                           uint64_t seq2) const;
  virtual void printDescription(std::ostream& out, bool deep) const {
    if (deep) {
      out << "gapInfo:" << std::endl;
      out << "std::vector<gapInfo> gapInfos_" << std::endl;
      for (const auto& g : gapInfos_) {
        g.printDescription(out, deep);
      }
    }
    out << "}" << std::endl;
  }
};

template<typename T, typename GAPPAR>
class alnInfoHolderBase {
public:
	// Constructors
	alnInfoHolderBase() {}
	alnInfoHolderBase(const std::string& directoryName,
			const std::string & alnType): alnType_(alnType){
	  auto allFiles = getFiles(directoryName, "", "file", false, false);
	  for (const auto &file : allFiles) {
	  	//std::cout << file.first << std::endl;
	  	//std::cout << "INDEX_" + alnType +".txt" << std::endl;
	    if (containsSubString(file.first, "README_" + alnType + ".txt")) {
	      readReadMeFile(file.first);
	    } else if (containsSubString(file.first, "INDEX_" + alnType +".txt")) {
	      readIndex(file.first);
	    }
	  }
	}
	alnInfoHolderBase(const gapScoringParameters <GAPPAR>& gapPars,
	                  const substituteMatrix & scoringArray,
	                  const std::string & alnType)
	      : gapPars_(gapPars), scoring_(scoringArray), alnType_(alnType) {

	}
	//members
  gapScoringParameters <GAPPAR> gapPars_;
  std::hash<std::string> hStr;
  substituteMatrix scoring_;
  std::string alnType_;
  std::unordered_map<uint64_t, std::unordered_map<uint64_t, T>>
        infos_;
  // functions
	void addAlnInfo(const std::string& seq1, const std::string& seq2,
									const T& info){
		uint64_t seq1Hash = hStr(seq1);
		uint64_t seq2Hash = hStr(seq2);
		//std::cout << "adding " << seq2 << " to " << seq1 << std::endl;
		addAlnInfo(seq1Hash, seq2Hash, info);
	}

	void addAlnInfo(uint64_t seq1Hash, uint64_t seq2Hash,
									const T& info){
	  if (infos_.find(seq1Hash) == infos_.end()) {
	  	//std::cout << "adding " << seq2Hash << " to " << seq1Hash << std::endl;
	    infos_.emplace(
	        seq1Hash, std::unordered_map<uint64_t, T>{{seq2Hash, info}});
	  } else if (infos_[seq1Hash].find(seq2Hash) != infos_[seq1Hash].end()) {
	    std::cout << "already added " << std::endl << seq2Hash << std::endl;
	    std::cout << "to " << std::endl << seq1Hash << std::endl;
	    exit(1);
	  } else {
	    infos_[seq1Hash].emplace(seq2Hash, info);
	  }
	}


	bool checkForAlnInfo(const std::string& seq1, const std::string& seq2){
		//std::cout << "bool checkForAlnInfo(const std::string& seq1, const std::string& seq2)" << std::endl;
	  uint64_t seq1Hash = hStr(seq1);
	  uint64_t seq2Hash = hStr(seq2);
		return checkForAlnInfo(seq1Hash, seq2Hash);
	}
	bool checkForAlnInfo(uint64_t seq1Hash, uint64_t seq2Hash){
		//std::cout << "bool checkForAlnInfo(uint64_t seq1Hash, uint64_t seq2Hash)" << std::endl;
		auto check = infos_.find(seq1Hash);
	  if (check == infos_.end()) {
	    return false;
	  } else if (check->second.find(seq2Hash) == check->second.end()) {
	    return false;
	  } else {
	    return true;
	  }
	}

	bool getAlnInfo(const std::string& seq1, const std::string& seq2, T & info){
		return getAlnInfo(hStr(seq1), hStr(seq2), info);
	}
	bool getAlnInfo(uint64_t seq1Hash, uint64_t seq2Hash, T & info){
		auto check = infos_.find(seq1Hash);
	  if (check == infos_.end()) {
	    return false;
	  } else {
	  	auto check2 = check->second.find(seq2Hash);
	  	if (check2 == check->second.end()) {
	  		return false;
	  	}else{
	  		info = check2->second;
	  		return true;
	  	}
	  }
	}

	void readReadMeFile(const std::string& filename){
	  //std::cout << "reading "+ alnType_ +"readme" << std::endl;
	  std::ifstream inFile;
	  inFile.open(filename);
	  std::vector<std::vector<int32_t>> arrayInVectors;
	  bool readingGaps = false;
	  bool readingArray = false;
	  for (std::string line; std::getline(inFile, line);) {
	    if (readingGaps) {
	      //std::cout << "gapLine: " << line << std::endl;
	      auto gapParsInfo =
	          convertStringToVector<GAPPAR>(line, ",");
	      //printVector(gapParsInfo);
	      gapPars_ =
	          gapScoringParameters<GAPPAR>(gapParsInfo[0], gapParsInfo[1], gapParsInfo[2],
	                               gapParsInfo[3], gapParsInfo[4], gapParsInfo[5]);
	      readingGaps = false;
	    }
	    if (readingArray) {
	      arrayInVectors.emplace_back(convertStringToVector<int32_t>(line, ","));
	    }
	    if (line == "GapPars:") {
	      readingArray = false;
	      readingGaps = true;
	    } else if (line == "ScoringArray:") {
	      readingArray = true;
	      readingGaps = false;
	    }
	  }

	  for (auto i : iter::range(arrayInVectors.size())) {
	    for (auto j : iter::range(arrayInVectors[i].size())) {
	      scoring_.mat_[i][j] = arrayInVectors[i][j];
	    }
	  }
	}
	void readIndex(const std::string& indexFilename){
	  //std::cout << "Reading " + alnType_  + " index file" << std::endl;
	  std::ifstream inFile;
	  inFile.open(indexFilename);
	  std::vector<std::string> info(400);
	  std::vector<std::string> inputGapInfo(3);
	  std::string out;
	  std::stringstream ss;
	  std::vector<gapInfo> gInfos;
	  for (std::string line; std::getline(inFile, line);) {
	    inputGapInfo.clear();
	    gInfos.clear();
	    ss.clear();
	    ss << line;
	  	uint32_t index = 0;
	    while (index < 2) {
	      ss >> out;
	      info[index] = out;
	      ++index;
	    }
	    addAlnInfo(std::stoul(info[0]), std::stoul(info[1]),
	    		T::readInfo(ss, info, inputGapInfo,gInfos, out ) );
	  }
	}
	void writeOutInfos(std::string parentDir,
										 std::string outDirName) const{
		//std::stringstream gapParsInfo;
		// just for right now just make it the data so we can examine the writing
		if (parentDir.back() != '/') {
			parentDir.append("/");
		}
		outDirName = parentDir + outDirName;
		if (outDirName.back() != '/') {
			outDirName.append("/");
		}
		int directoryStatus = mkdir(outDirName.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
		if (directoryStatus != 0) {
			// if directory already exits do nothing i guess
		} else {
			chmod(outDirName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		}
		// write out info for readMeFile
		if (!fexists(outDirName + "README_" + alnType_ + ".txt")) {
			std::ofstream outReadMeFile;
			openTextFile(outReadMeFile, outDirName + "README_" + alnType_ + ".txt", ".txt", false,
									 false);
			outReadMeFile << "GapPars:" << std::endl;
			gapPars_.writePars(outReadMeFile);
			outReadMeFile << "ScoringArray:" << std::endl;
			for (auto i : iter::range(scoring_.mat_.size())) {
				for (auto j : iter::range(scoring_.mat_[i].size())) {
					if (0 != j) {
						outReadMeFile << ",";
					}
					outReadMeFile << scoring_.mat_[i][j];
				}
				outReadMeFile << std::endl;
			}
		}
		std::ofstream indexFile;
		std::string indexFilename = outDirName + "INDEX_" + alnType_ + ".txt";
		indexFile.open(indexFilename, std::ios::app);

		// openTextFile(indexFile, , ".txt" ,false, true);
		uint64_t alnCount = 0;
		uint64_t alnAddFromFileCount = 0;
		uint64_t alnFromThisCount = 0;
		for (const auto &infoMap : infos_) {
			for (const auto &infoMapSub : infoMap.second) {
				++alnCount;
				if (!infoMapSub.second.addFromFile_) {
					infoMapSub.second.writeInfoSingleLine(indexFile, infoMap.first,
																								infoMapSub.first);
					++alnFromThisCount;
				} else {
					++alnAddFromFileCount;
				}
			}
		}
	}
};
template<typename GAPPAR>
class alnInfoMasterHolder {

 public:
  // constructors
	alnInfoMasterHolder() {};
  alnInfoMasterHolder(const gapScoringParameters <GAPPAR>& gapPars,
  	  const substituteMatrix & scoringArray):localHolder_(std::unordered_map<std::string, alnInfoHolderBase<alnInfoLocal, GAPPAR>> {{gapPars.getIdentifer(),alnInfoHolderBase<alnInfoLocal, GAPPAR>(gapPars,scoringArray, "LOCAL")} }),
  	  		globalHolder_(std::unordered_map<std::string, alnInfoHolderBase<alnInfoGlobal, GAPPAR>>{{gapPars.getIdentifer(),alnInfoHolderBase<alnInfoGlobal, GAPPAR>(gapPars,scoringArray, "GLOBAL")} }){};
	alnInfoMasterHolder(const std::string &masterDirName, const gapScoringParameters <GAPPAR>& gapPars,
  	  const substituteMatrix & scoringArray) {
	  std::cout << "reading in previous alignments" << std::endl;
	  auto allDirectories = getFiles(masterDirName, "", "directory", false, false);
	  for (const auto &dir : allDirectories) {
	    std::cout << "directory name " << dir.first << std::endl;
	    std::cout << "reading in local" << std::endl;
	    alnInfoHolderBase<alnInfoLocal, GAPPAR> currentLocalHolder(dir.first, "LOCAL");
	    std::cout << "reading in global" << std::endl;
	    alnInfoHolderBase<alnInfoGlobal, GAPPAR> currentGlobalHolder(dir.first, "GLOBAL");

	    std::cout << "local: " << currentLocalHolder.gapPars_.getIdentifer()
	              << std::endl;
	    std::cout << "global: " << currentGlobalHolder.gapPars_.getIdentifer()
	              << std::endl;

	    localHolder_[currentLocalHolder.gapPars_.getIdentifer()] =
	        currentLocalHolder;
	    globalHolder_[currentGlobalHolder.gapPars_.getIdentifer()] =
	        currentGlobalHolder;
	  }
	  if(allDirectories.empty()){
	  	*this = alnInfoMasterHolder(gapPars, scoringArray);
	  }
	}
  // members
  std::unordered_map<std::string, alnInfoHolderBase<alnInfoLocal, GAPPAR>> localHolder_;
  std::unordered_map<std::string, alnInfoHolderBase<alnInfoGlobal, GAPPAR>> globalHolder_;
  std::hash<std::string> strH_;
  // writing
  void write(const std::string &masterDirName) {
    int directoryStatus =
        mkdir(masterDirName.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
    if (directoryStatus != 0) {
      // if directory already exits do nothing i guess
    } else {
      chmod(masterDirName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    // write out the alignment infos
    for (const auto &holder : localHolder_) {
      holder.second.writeOutInfos(masterDirName, "alnInfo_" + holder.second.gapPars_.getIdentifer());
    }
    for (const auto &holder : globalHolder_) {
    	std::cout << "currentHoldr: " << holder.first << std::endl;
      holder.second.writeOutInfos(masterDirName, "alnInfo_" + holder.second.gapPars_.getIdentifer());
    }
  }
};
} // compro
