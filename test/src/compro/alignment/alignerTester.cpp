#include <catch.hpp>

#include "../../src/compro/alignment/aligner.hpp"
#include "../../src/compro/randomStringsGen.h"
using namespace compro;

TEST_CASE("Basic tests for aligner", "[aligner]" ){
  SECTION("global alignSeq constant gap pen"){
    gapScoringParameters<int32_t> gapParsOne(5,5);
    substituteMatrix blosum62;
    blosum62.setWtihBlosum62();
    aligner<int32_t> alignerObjTest(1000, gapParsOne, blosum62);
    std::string firstTest = "ILYPRQSMICMSFCFWDMWKKDVPVVLMMFLERRQMQSVFSWLVTVKTDCGKGIYNHRKYLGLPTMTAGDWHWIKKQNDPHEWFQGRLETAWLHSTFLYWKYFECDAVKVCMDTFGLFGHCDWDQQIHTCTHENEPAIAFLDLYCRHSPMCDKLYPVWDMACQTCHFHHSWFCRNQEMWMKGDVDDWQWGYHYHTINSAQCNQWFKEICKDMGWDSVFPPRHNCQRHKKCMPALYAGIWMATDHACTFMVRLIYTENIAEWHQVYCYRSMNMFTCGNVCLRCKSWIFVKNYMMAPVVNDPMIEAFYKRCCILGKAWYDMWGICPVERKSHWEIYAKDLLSFESCCSQKKQNCYTDNWGLEYRLFFQSIQMNTDPHYCQTHVCWISAMFPIYSPFYTSGPKEFYMWLQARIDQNMHGHANHYVTSGNWDSVYTPEKRAGVFPVVVPVWYPPQMCNDYIKLTYECERFHVEGTFGCNRWDLGCRRYIIFQCPYCDTMKICYVDQWRSIKEGQFRMSGYPNHGYWFVHDDHTNEWCNQPVLAKFVRSKIVAICKKSQTVFHYAYTPGYNATWPQTNVCERMYGPHDNLLNNQQNVTFWWKMVPNCGMQILISCHNKMKWPTSHYVFMRLKCMHVLMQMEYLDHFTGPGEGDFCRNMQPYMHQDLHWEGSMRAILEYQAEHHRRAFRAELCAQYDQEIILWSGGWGVQDCGFHANYDGSLQVVSGEPCSMWCTTVMQYYADCWEKCMFA";
    std::string secondTest = "ILIPRQQMGCFPFPWHFDFCFWSAHHSLVVPLNPQMQTVFQNRGLDRVTVKTDCHDHRWKWIYNLGLPTMTAGDWHFIKKHVVRANNPHQWFQGRLTTAWLHSTFLYKKTEYCLVRHSNCCHCDWDQIIHTCAFIAFLDLYQRHWPMCDKLYCHFHHSWFCRNQEMSMDWNQWFPWDSVPRANCLEEGALIALYAGIWANSMKRDMKTDHACTVRLIYVCELHAWLKYCYTSINMLCGNVCLRCKSWIFVKLFYMYAPVVNTIEANSPHYYKRCCILGQGICPVERKSHCEIYAKDLLSFESCCSQKQNCYTDNWGLEYRLFFQHIQMECTDPHANRGWTSCQTAKYWHFNLDDRPPKEFYMWLQATPTDLCMYQHCLMFKIVKQNFRKQHGHANPAASTSGNWDSVYTPEKMAYKDWYVSHPPVDMRRNGSKMVPVWYPPGIWHWKQSYKLTYECFFTVPGRFHVEGTFGCNRWDHQPGTRRDRQANHQFQCPYSDTMAIWEHAYTYVDQWRSIKEGQMPMSGYPNHGQWNVHDDHTNEQERSPICNQPVLAKFVRSKNVSNHEICKKSQTVFHWACEAQTNVCERMLNNQHVAVKRNVTFWWQMVPNCLWSCHNKMTWPTRPEQHRLFFVKMRLKCMHEYLDVAPSDFCRNMQAYMHSMRAILEYQADFDLKRRLRAIAPMDLCAQYDQEIILWSGGYIYDQSLQVVSCEGCSYYADCYVKCINVKEKCMFA";
    alignerObjTest.alignSeq(firstTest, secondTest, false);
    std::string ansA = "ILYPRQSMICMSFCF-WDM--WKKDVPVVLMMFLERRQMQSVF-S-WL--VTVKTDCGKGIYNHR-K--Y-LGLPTMTAGDWHWIKK---Q-NDPHEWFQGRLETAWLHSTFLYWKYFE-CDAVKVCMDTFGLFGHCDWDQQIHTCTHENEPAIAFLDLYCRHSPMCDKLYPVWDMACQTCHFHHSWFCRNQEMWMKGDVDDWQWGYHYHTINSAQCNQWFKEICKDMGWDSVFPPRHNCQRHKKCMPALYAGIW---MA----TDHACTFMVRLIYTENIAEWHQVYCYRSMNMFTCGNVCLRCKSWIFVKN-YMMAPVVNDPMIEA--FYKRCCILGKAWYDMWGICPVERKSHWEIYAKDLLSFESCCSQKKQNCYTDNWGLEYRLFFQSIQMN-TDPH----Y--CQTHVCW-ISAMF-PIYSPFYT--SG-PKEFYMW---LQARI-DQNM---HGHANHYV-TSGNWDSVYTPEKRA--G--V-FP-V-V-------VPVWYPPQMCN--D-YIKLTYEC--E---RFHVEGTFGCNRWD-L-GCRR--YII--FQCPYCDTMKI---CY--VDQWRSIKEGQFRMSGYPNHGYWFVHDDHTNEW-----CNQPVLAKFVRSKIVA---ICKKSQTVFHYAYTPGYNATWPQTNVCERMYGPHDNLLNNQQNVTFWWKMVPNCGMQILISCHNKMKWPT--S-HYVF---MRLKCMHVLMQMEYLDHFTGPGEGDFCRNMQPYMHQDLHWEGSMRAILEYQAEHH-RRAFRA----ELCAQYDQEIILWSGGWGVQDCGFHANYDGSLQVVSGEPCSMWCTTVMQYYADCWEKCMFA";
    std::string ansB = "ILIPRQQMGCFPFPWHFDFCFWSAHHSLVVP--LNP-QMQTVFQNRGLDRVTVKTDC----HDHRWKWIYNLGLPTMTAGDWHFIKKHVVRANNPHQWFQGRLTTAWLHSTFLY-KKTEYC-LVR---HS-NCC-HCDWDQIIHTCAF-----IAFLDLYQRHWPMCDKLY------C---HFHHSWFCRNQEMSM--D---W---------N--Q---WFP-------WDSV-P-RANCLE-EGALIALYAGIWANSMKRDMKTDHACT--VRLIYVCELHAWLK-YCYTSINML-CGNVCLRCKSWIFVKLFYMYAPVVNTIEANSPHYYKRCCILGQ------GICPVERKSHCEIYAKDLLSFESCCSQK-QNCYTDNWGLEYRLFFQHIQMECTDPHANRGWTSCQTAKYWHFNLDDRPP-KEFYMWLQATPTDLCMYQHCLMFKIVKQNFRKQHGHANPAASTSGNWDSVYTPEKMAYKDWYVSHPPVDMRRNGSKMVPVWYPPGIWHWKQSY-KLTYECFFTVPGRFHVEGTFGCNRWDHQPGTRRDRQANHQFQCPYSDTMAIWEHAYTYVDQWRSIKEGQMPMSGYPNHGQWNVHDDHTNEQERSPICNQPVLAKFVRSKNVSNHEICKKSQTVFHWA-C---EA---QTNVCERMLN-NQHVAV-KRNVTFWWQMVPNC----LWSCHNKMTWPTRPEQHRLFFVKMRLKCMH-----EYLD--VAPS--DFCRNMQAYMH-------SMRAILEYQADFDLKRRLRAIAPMDLCAQYDQEIILWSGGY-I--------YDQSLQVVSCEGCSYYADCYVKCI-NVKEKCMFA";
    int32_t ansScore = 1555;
    REQUIRE(ansA == alignerObjTest.alignObjectA_);
    REQUIRE(ansB == alignerObjTest.alignObjectB_);
    REQUIRE(ansScore == alignerObjTest.parts_.score_);
  }
  SECTION("local alignSeq constant gap pen"){
    gapScoringParameters<int32_t> gapParsOne(5,5);
    substituteMatrix pam250;
    pam250.setWithPam250();
    aligner<int32_t> alignerObjTest(1000, gapParsOne, pam250);
    std::string firstTest = "AMTAFRYRQGNPRYVKHFAYEIRLSHIWLLTQMPWEFVMGIKMPEDVFQHWRVYSVCTAEPMRSDETYEQKPKPMAKWSGMTIMYQAGIIRQPPRGDRGVSDRNYSQCGKQNQAQLDNNPTWTKYEIEWRVQILPPGAGVFEGDNGQNQCLCPNWAWEQPCQWGALHSNEQYPNRIHLWAPMSKLHIKIEKSSYNRNAQFPNRCMYECEFPSYREQVDSCHYENVQIAFTIFSGAEQKRKFCSCHFWSNFIDQAVFSTGLIPWCYRRDDHSAFFMPNWNKQYKHPQLQFRVAGEGTQCRPFYTREMFTKVSAWRIAGRFAGPYERHHDAHLELWYQHHKVRTGQQLGIIWNNRDKTRNPCPFSAYYNKLPWWKINQNAFYNCLQNIAHSTHDETHEFNPVKCIDWLQGTMVPTECKKGFVHEKCECYRNPGPPLHDMYHQMEDIFGVRFDCLTGWKHLSDYNPCQERRNINDFYIFAYEIAPAVKNLVLSPQPLADATKKCAFNYTPLDQSPVVIACKWYIHQPICMLLIVLICAMDKYNAHMIVIRTTEGQQPMHACRMTEGPGMCMKEPLVTFTLPAQWQWPNHEFKYVYMYVLNYHLSQYTYTDEGHAGGQHYSFNVAVDVGMAWGHNRCYCQPACYSQQETQTRTIDYEKWQYMKHQAFKWGLWFCEQERHAWFKGQNRCEMFTAKMTRMGADSNLDQYKLMLAQNYEEQWEQPIMECGMSEIIEIDPPYRSELIFTFWPFCTYSPWQNLIKCRCNNVIEEMDQCVPLTFIGFGVKQAGGIQAWAFYKEEWTSTYYLMCQCMKSDKAQYPYEIILFWMQPMDTGEQEPPQQNMWIFLPHSWFFDWCCNAPWSEICSSRHDHGQCQDAFYPCELFTVFDDIFTAEPVVCSCFYDDPM";
    std::string secondTest = "WQEKAVDGTVPSRHQYREKEDRQGNEIGKEFRRGPQVCEYSCNSHSCGWMPIFCIVCMSYVAFYCGLEYPMSRKTAKSQFIEWCDWFCFNHWTNWAPLSIVRTSVAFAVWGHCWYPCGGVCKTNRCKDDFCGRWRKALFAEGPRDWKCCKNDLQNWNPQYSQGTRNTKRMVATTNQTMIEWKQSHIFETWLFCHVIIEYNWSAFWMWMNRNEAFNSIIKSGYPKLLLTQYPLSQGSTPIVKPLIRRDQGKFWAWAQMWWFREPTNIPTADYCHSWWQSRADLQNDRDMGPEADASFYVEFWYWVRCAARTYGQQLGIIWNNRLKTRNPCPYSADGIQNKENYVFWWKNMCTKSHIAFYYCLQNVAHYTHDVTAEFNPVKCIDWLQGHMVLSSWFKYNTECKKLFVHEKCECYRMFCGVVEDIFGVRFHTGWKHLSTAKPVPHVCVYNPSVQERRNINDFYIFYEIAPAVKNLVLSAQPLHDYTKKCAFNYTPITITRIISTRNQIIWAHVVIACQFYSPHQMLLIELAMDKYCADMNVRRSTEGHQPMHACRSTFGPGMAAKEPLVTFTLVAFWQWPNHEFQYVYMYTEDKIIQIGPHLSNGCEMVEYCVDCYAKRPCYRAYSAEAQYWRMITEAEDYSYKTRNAIAATATVRGQYCHPFRWLGIVWMAHHDCFFANECGTICIPQMAEMRPPETTPYEIDIIFMMFWKEHMSTTILDVVGMYRPATFSHWHDAHHQCEPYLTPLMCQSKLVFDAAFTQVGVKGVWYHTEKLELMAGFNHMKFKKEEAQQSCFYWFQDCPDYDPPDAVRKTDEKHIRAHGEIWWLMRYYCMYHILHIASRHEWMHLRWDQACTNPGYELFEFIPWVLRRYVVYDKIRYNYSYRNSASMEFV";
    alignerObjTest.alignSeq(firstTest, secondTest, true);
    std::string ansA = "YQAGIIRQPPRGD-RGVSDRNYSQCGKQ-NQ-AQLDNNPTWTKYEIEWRVQI-LPPGAGVFEGDNGQNQCLCPNW--A-W-EQPCQW----GALHS-NEQYPNRIHLWAPMSKLHIKIEKSSYN-RNAQ-FPNRCMYECE-FPSY-REQVDSCHYENVQIAF-TIFSGAEQKRKFCSCHFWSNFIDQAVFSTGLI-PWCYRRDDHSAFFMPNWNKQ--YKHPQLQFRVAGEGTQCRPFYTREMFTKVSAWRIAGRFAGPYERHHDAHLELWY-QHHKVRT-GQQLGIIWNNRDKTRNPCPFSAY-Y-NK--LP-WWK-I-NQ-N-AFYNCLQNIAHSTHDETHEFNPVKCIDWLQGTMV-P------TECKKGFVHEKCECYRNPGPPLHDMYHQMEDIFGVRFDCLTGWKHLS------D---YNPC-QERRNINDFYIFAYEIAPAVKNLVLSPQPLADATKKCAFNYTPLDQSPVVIACK---WYIHQPI-CMLL----IVLIC-AMDKYNAHMIVIRTTEGQQPMHACRMTEGPGMCMKEPLVTFTLPAQWQWPNHEFKYVYMYVLNYHLSQYTYTDEGHAGGQHYSFNVAVDVGMAWGHNRCYCQPACYSQQETQTRTIDYEKWQYMKHQAFKWGLWFCEQER-HA--WFKGQNRCEMFTAKMTRMGADSNLDQYKLMLAQNYEEQWEQPIMECGMSEIIEIDPPYRSELIFTFWPFCTYSPWQNLIKCRCNNVIEEMDQCVP-LTF-IGFGVKQAGGIQA-WAFYKE--EWTSTYYLMCQCMKSDKAQYPYEIILFWMQ--P-MDTGE--QEPPQQNMWIFLPHSWFFDWCCNAPWSEICSSRHD--H---GQ-CQDAFYPCELFTVF";
    std::string ansB = "Y-P-MSRKTAKSQFIEWCDW-F--CFNHWTNWAPLSIVRTSVAFAV-W-GHCWYPCG-GVCKTNRCKDD-FCGRWRKALFAEGPRDWKCCKNDLQNWNPQYSQGTR--NTK-RMVATTNQTMIEWKQSHIFETW-LF-CHVIIEYNWSAF-W-MWMNRNEAFNSIIKSGYPKLLL-T-QY-P-L-SQG--STPIVKPL-IRRD-QGKFW-A-WAQMWWFREPT-NIPTA-D-Y-CHSW--WQ--SR-ADLQ-NDRDMGP-EADASFYVEFWYWVRCAARTYGQQLGIIWNNRLKTRNPCPYSADGIQNKENYVFWWKNMCTKSHIAFYYCLQNVAHYTHDVTAEFNPVKCIDWLQGHMVLSSWFKYNTECKKLFVHEKCECYRM----FCGV---VEDIFGVRFH--TGWKHLSTAKPVPHVCVYNPSVQERRNINDFYIF-YEIAPAVKNLVLSAQPLHDYTKKCAFNYTPITITRIISTRNQIIW-AHVVIACQFYSPHQMLLIELAMDKYCADMNVRRSTEGHQPMHACRSTFGPGMAAKEPLVTFTLVAFWQWPNHEFQYVYMYTED-KIIQIG-PHLSN-GCEMVEYCVDC-YAK-RPCYRAYSAEAQYWRMITEAEDYSYKTRNAIAATATVRGQ-YCHPFRWLGIVWM-AHHDC-FFANECGTICI-PQMAEMRPPETTPYEI--DIIFMMF-WKE--HMSTTIL-DVVGMYRP-ATFSHWHDAHH-QCEPYLTPL-MCQSKLVFDAAFT--QVG-VKGVW-YHTEKLELMAGFNHM-K-FKKEEAQ---QSCFYWFQDCPDYDPPDAVRKTDEKHIRAHGEIWWLMRYYCMYHILHI-ASRHEWMHLRWDQACTNPGY--ELFE-F";
    int32_t ansScore = 1062;
    REQUIRE(ansA == alignerObjTest.alignObjectA_);
    REQUIRE(ansB == alignerObjTest.alignObjectB_);
    REQUIRE(ansScore == alignerObjTest.parts_.score_);
  }

  SECTION ("global alignSeq affine gap pen"){
    gapScoringParameters<int32_t> gapParsOne(11,1);
    substituteMatrix blosum62;
    blosum62.setWtihBlosum62();
    aligner<int32_t> alignerObjTest(1000, gapParsOne, blosum62);
    std::string firstTest = "YHFDVPDCWAHRYWVENPQAIAQMEQICFNWFPSMMMKQPHVFKVDHHMSCRWLPIRGKKCSSCCTRMRVRTVWE";
    std::string secondTest = "YHEDVAHEDAIAQMVNTFGFVWQICLNQFPSMMMKIYWIAVLSAHVADRKTWSKHMSCRWLPIISATCARMRVRTVWE";
    alignerObjTest.alignSeq(firstTest, secondTest, false);
    std::string ansA = "YHFDVPDCWAHRYWVENPQAIAQME-------QICFNWFPSMMMK-------QPHVFKV---DHHMSCRWLPIRGKKCSSCCTRMRVRTVWE";
    std::string ansB = "YHEDV----AHE------DAIAQMVNTFGFVWQICLNQFPSMMMKIYWIAVLSAHVADRKTWSKHMSCRWLPI----ISATCARMRVRTVWE";
    int32_t ansScore = 144;
    REQUIRE(ansA == alignerObjTest.alignObjectA_);
    REQUIRE(ansB == alignerObjTest.alignObjectB_);
    REQUIRE(ansScore == alignerObjTest.parts_.score_);
  }
  
  SECTION ("local alignSeq affine gap pen"){
    gapScoringParameters<int32_t> gapParsOne(11,1);
    substituteMatrix blosum62;
    blosum62.setWtihBlosum62();
    aligner<int32_t> alignerObjTest(1000, gapParsOne, blosum62);
    std::string firstTest = "YHFDVPDCWAHRYWVENPQAIAQMEQICFNWFPSMMMKQPHVFKVDHHMSCRWLPIRGKKCSSCCTRMRVRTVWE";
    std::string secondTest = "AHEDAIAQMVNTFGFVWQICLNQFPSMMMKIYWIAVLSAHVADRKTWSKHMSCRWLPIISATCARMRVRTVWE";
    alignerObjTest.alignSeq(firstTest, secondTest, true);
    std::string ansA = "AIAQME-------QICFNWFPSMMMK-------QPHVFKV---DHHMSCRWLPIRGKKCSSCCTRMRVRTVWE";
    std::string ansB = "AIAQMVNTFGFVWQICLNQFPSMMMKIYWIAVLSAHVADRKTWSKHMSCRWLPI----ISATCARMRVRTVWE";
    int32_t ansScore = 140;
    REQUIRE(ansA == alignerObjTest.alignObjectA_);
    REQUIRE(ansB == alignerObjTest.alignObjectB_);
    REQUIRE(ansScore == alignerObjTest.parts_.score_);
  }
  SECTION ("comparing cache versus regular global"){
    gapScoringParameters<uint32_t> gapPars(5, 1);
    substituteMatrix scoreMatrix(2, -2);
    aligner<uint32_t> alignerObj(500, gapPars, scoreMatrix);
    aligner<uint32_t> alignerObjCache(500, gapPars, scoreMatrix);
    randomGenerator gen;
    std::vector<std::string> randStrings = evenRandStrsRandLen(
        100, 100, std::vector<char>{'A','C','G','T'}, std::vector<uint32_t>{1,1,1,1}, gen, 50);
    for(const auto & pos : iter::range(randStrings.size())){
    	for(const auto & secondPos : iter::range((randStrings.size()))){
    		alignerObj.alignSeq(randStrings[pos], randStrings[secondPos], false);
    		alignerObjCache.alignSeqCache(randStrings[pos], randStrings[secondPos], false);
        REQUIRE(alignerObjCache.alignObjectA_ == alignerObj.alignObjectA_);
        REQUIRE(alignerObjCache.alignObjectB_ == alignerObj.alignObjectB_);
        REQUIRE(alignerObjCache.parts_.score_ == alignerObj.parts_.score_);
    	}
    }
    //second round around so should be cached now
    for(const auto & pos : iter::range(randStrings.size())){
    	for(const auto & secondPos : iter::range((randStrings.size()))){
    		alignerObj.alignSeq(randStrings[pos], randStrings[secondPos], false);
    		alignerObjCache.alignSeqCache(randStrings[pos], randStrings[secondPos], false);
        REQUIRE(alignerObjCache.alignObjectA_ == alignerObj.alignObjectA_);
        REQUIRE(alignerObjCache.alignObjectB_ == alignerObj.alignObjectB_);
        REQUIRE(alignerObjCache.parts_.score_ == alignerObj.parts_.score_);
    	}
    }
  }
  SECTION ("comparing cache versus regular local"){
    gapScoringParameters<uint32_t> gapPars(5, 1);
    substituteMatrix scoreMatrix(2, -2);
    aligner<uint32_t> alignerObj(500, gapPars, scoreMatrix);
    aligner<uint32_t> alignerObjCache(500, gapPars, scoreMatrix);
    randomGenerator gen;
    std::vector<std::string> randStrings = evenRandStrsRandLen(
        100, 100, std::vector<char>{'A','C','G','T'}, std::vector<uint32_t>{1,1,1,1}, gen, 50);
    for(const auto & pos : iter::range(randStrings.size())){
    	for(const auto & secondPos : iter::range((randStrings.size()))){
    		alignerObj.alignSeq(randStrings[pos], randStrings[secondPos], true);
    		alignerObjCache.alignSeqCache(randStrings[pos], randStrings[secondPos], true);
        REQUIRE(alignerObjCache.alignObjectA_ == alignerObj.alignObjectA_);
        REQUIRE(alignerObjCache.alignObjectB_ == alignerObj.alignObjectB_);
        REQUIRE(alignerObjCache.parts_.score_ == alignerObj.parts_.score_);
    	}
    }
    //second round around so should be cached now
    for(const auto & pos : iter::range(randStrings.size())){
    	for(const auto & secondPos : iter::range((randStrings.size()))){
    		alignerObj.alignSeq(randStrings[pos], randStrings[secondPos], true);
    		alignerObjCache.alignSeqCache(randStrings[pos], randStrings[secondPos], true);
        REQUIRE(alignerObjCache.alignObjectA_ == alignerObj.alignObjectA_);
        REQUIRE(alignerObjCache.alignObjectB_ == alignerObj.alignObjectB_);
        REQUIRE(alignerObjCache.parts_.score_ == alignerObj.parts_.score_);
    	}
    }
  }
}
