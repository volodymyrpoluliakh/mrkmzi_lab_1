#include "big_int.h"
#include <iostream>
#include <vector>
#include <string_view>
#include <algorithm>
#include <tuple>
#include <gmp.h>
#include <chrono>
#include <vector>
#include <string>

#include <boost/algorithm/string.hpp>

namespace {
std::string allowed_operators = {'+','-','*','^','%'};

std::vector<std::string> num_512_strs = {
    "D79B7CD117FC7B43FFFAE6C01A693EC4B8668402DCC990F6D72B61FF7736FE3CF3C45D5197F95C2467876ADCC1990D8342E4B64E32B22484BB735431C231DD11",
    "DE44CC22733B4820624E8DCEE0B24CC3BA4FE2CC57CB2B28C4368B25E141D033615E6516BDF67C5FEECF0EC93689BDC0CC4EE04F767603C110F02C5F00F99D69",
    "D68D240DF80FF6FA7E8D02C156971BFBC80F4EDA8E0A398DFE48DC2B5435012BABEE9F437FC8987BA690ACD344D6386932F3B5D3820F05431C47B3ADF0D84F73",
    "DF2D02002513D292182623ACBC8FE7403368BAC6F0295ED9E8F51818D4E14AC5CF18FACFCD8E85EB3E53622B1C86C39632923D05B8CBB999D76EC8B7EDBF8AEB",
    "C395050DAC999B48F75C4CBA2200CE8D5D99CD4E6373921FA5CE476F6A0A0FF09ED234EE9D0968E13A28D8355545B2FDBCC82B30DFAD88CEA6BBC46542431A5D",
    "CC665F6C29FBD3EC98B2A20B76FBA1965E45429E227910E66BA699537640464CF739D7BDB6F4ECF9BFA237A8361553C78753353C6DEF3C95DC46C60597B05B3D",
    "E15CEF9A5F604FFF5AD90F549F8DE4BC9A46F39D0E2F81994F858B5117FEDC8A99A1BBCD26F0E82F1F9C601C989B0C9D72DA31799B1E7B5D2E00ADBC6FB4C2C1",
    "F05A14BE491FF564BC77F8CB022FC1E3752CECBB818342175C25DF2032356834721F953617401A8C18E47421DFC4818BAE7116C5BA6814851728768B00419585",
    "D5743A8518B249172CA72BBC29D3B45B1E2CCF2949991C073ECB361C1EC2D0DD4F51CD6063503F58C9213200ACCF876C0852D9F19C72F19E05783BD80DEF60BD",
    "CD590C45FEACBCF5C66B98A359123108A1F7BB0E37B466033E7E37CB4190BABE139F84EFFF5FF1E097C6AD93AE683EEF49F0AA46D5D86634D022B8249E54BF67",
};

std::vector<std::string> num_1024_strs = {
/* 1 */   "C848FA0BBA000E3C7EF6C0088610DBDAA584DDDE79970CEE5E464667E5EA552889BED0A5EF15C4D0652AE2E6551EAB6E9D697B00DBAC7F95E6741E74A637A8DFA1F4D63EFD7C57EE8101D662BC14A8B6C8BDD9F27746CFEA3435E535E5653BF08F80A164B5C62FDBC5ECBFD39DF92FEA585124D4931F5469A47DD73626889A81",
/* 2 */   "C7FA7421ABD527E68E9DBC8C7C6C401ACDC51F6F344244B4B42D123D5259B8D8EFE622C86C977E72A9334212A2B129507B8C7C4F805DE8914C021093E0057354C826C3CA4626F4825CC2C6410CB40480CEF8382A3F54962FCC79B3DCE27C9775A4B2766F377EC934140121EAF5D276DE85309D2F5297AE4A3408601E9333A1FB",
/* 3 */   "E5D47B2822A0646032194A13CC4B70BAC2751092BB9FDCD05E08EDF9551A999637B1F5518A6E3C5D16FFAF6C0E93E74C2B0D20C27C2FB034ED58121338D608C7039A5DE48823A702E34797458B60AC443C702C94C135431B774E9528E4CB8E8A8FFBD71411DF488D031B6CCFFFEC6F3460B595359DD100FF716BAF0A6B6AA863",
/* 4 */   "D55803E961656D1120435D7F67D55F66FCADC6F9CE45F0E3A08E6FCFFA672CDF577A464718535DAADC3D6AFA0EDB4BACACAA2AB8BE30423115FB8E5F10DC87B30DF3465F1A2B420F4920CA8CF6B2F34147AD1F57128C4BD83DADDE7363EC8A25E0C364BC454000B604AA9ADCD1FF9B50066D4C6485339B1AAF7F136F7A983421",
/* 5 */   "F352F2D987024726C3B231F10B054D1C633C1A4D453F584274A233229900A935AF0B9CFF99EC1D7A28AFFD8E299072982E1E73F965B10DA4314451C93C95016906790F834EBE552963B8028E04E6525112F9C5009666D205A74C8642650B7EE32FEE55E92BFAF0BFD4B0CF32AB2B59B8B88E792B7D989F6D3E6863442A3DD50D",
/* 6 */   "C674F4ED3A65F03262DF2AE1B1C6F735ED4B9B0A3747E7E5187A13AF4E59353329FC20D818182C47EB01D20D1B020F02684E1BE9501A361803C2C24E8770D66F14A6F8B311CB840AEAB6EBBA8166B055B80E9C5AD053DD9CF23517110B874EAE7363A4B72386126AFA437412564DE8D0E8E29168DA56A2CB81044B505AE10383",
/* 7 */   "D47FA8D4A4E35198D1753EAB572BD9644B9C9D3E71018EA9DA436CC4E4378AED17C14B1B808B5973E3E4A918EEE881510230B159CBF1E716F9E7F181B6D7909647B394ADF62860D62827D21A9F095C08BABFA774B42B8A3021105BE7F9819F1856CCA5A216AA5261E9F10DF0BBAA11C547DF432968A0AF70A2272220FF39488B",
/* 8 */   "D5400935329D837194A8EC07F415F0B17C5D52B839E5CC228D5856EB2696CC29E5EB897E7AE7DA62ACF6E6EC23069B3056B17AAE348F7F9F7A4DD73DE2624EEBA92A4DBACB16F5F7A936F321A6DADD6CE39B5E4A0AB444AC25E77AA85E0E2CC777EA03213EABF344E7B49C7FC23BEA271525CE6FE8E7A60A43A21056492724CB",
/* 9 */   "CD223A6A41A54B6DF535CE1FD1FA0F55954EAD533E53510A345CA91EA602A4108A3A11BD445DE0E63E12A9D90120F34FE9FDDFA788D53AFF08BD8421C4C55523E113510DD59862AB35B31AA2FE3C443AF7E011944CBD4BD63FB2C91A232006050D2697F2217B0C8FC0D664761D58F0829CAABDD8068DEF82A3AAB8D6E66EB1E3",
/* 10 */  "DD820087392E32E1755657E10124BA42CA38CBBE96604D7BBD9BF6EA807D375D2A7DDB3B6EF9F0F97A523DAA97D241C6DFD5F995AD92E263A4CA35EBE71017B7A9F9177FE2CA8C783635495990EF332D54107E90828538BB4DAA5D28096F9958456B922E366D0248310DB4C33E29C1F20283F5CE8BA0CDEE78A3EB3F67BC0F8F",
};

std::vector<std::string> num_2048_strs = {
/* 1 */   "D2A1391CFB4E87C1D2CFDA5EDCE1A0572EDAFC382F3E795F1C4FD458BF3B9C999CD8E729FDE6E975AE0C7873D6F8EDE8927F9CC88DE889FBAF8F764ACA4A972D522F552448E77DE0EE163C1983461A8C4E3B78376258B0B7A451E9BEA1F30FF44A871BFDA94E1E59CDCD042BC3B39DF1DDD3BA84C463951FC67858EE08C9FA7F45A32BB8C8AF56E93358E5BEE0DEF61A8162A795902DF8459A086D94062E815D9DF8BB49E2455BC567008BA974D76A0FB9B78F81EAF2A2346B61F2A6EA9A66CD8F667BDFB61DAE7B115FD85FB0B9CF0AB2B06A38953288D2FF76B10DF6728C102CABED560EA06E2724F330A9D68C04B8B8213E84BAB15BEF3C7B7E2FB5F34D33",
/* 2 */   "D7AB377D714C44D06678CC322BD52A3D22BDDC5866576CF0B7B9D2A36659620335FE62EE25191425496120475940DF260C57A202AB128882F5B3CE58B13A5A8753A225AAAF66687D568875ACDAA4DF4A113F3C8AFB3E10D941A8CD51BBB5A1F9A346A0237F72DE814C8D5F4F1EE58D7B660AB5911B25CE8616E255817586D089BF1FDE250E8F2CCA069F61441770BB7AB60EACA8E6B7EAA6CBAF23ABCE998478A93BA3F0F97CF5E50A47F72B20E310EF23C2CE42D6A282A0EFE4B0B6F5317204DA2634ACC729933C1CEC8A8AA933DEC9EA8E253336DC9F9D0A65A7D22F880EA0E44B8C99BBABDF54C25F29A0884037B19F4D98AAA2C64EA944B3F89E88897AC3",
/* 3 */   "DC225A7F7653B0769B40EAB4C5EA0DBC5BBBC1F8691AA2840233FDB3FAE73583FB101FE268FB78C78B305A8C45F00298495B4B093F3624D8D67E86E4FD92DDA7C635B47046255CAAF2B521B9FFA741B25DD3417816AC1222BD2C7DE1305151E1B8C9A5C8F6BD2DBFF6BF7A376B661D3F3A85817403B8C0636090FAD7AF90A1D114E8B23FB02AB138B141A23C6401BCC717430A1D4877E9A39982D89FDC0AC079F1273A947683C7865E755B5D969530DEBA4EB5EAEAD6CB11A6ECFC8379712BA4F33F8BE004A84C39E4C8F81A88EF3902A57C95262F04CDDB9BFE26EEE5F204690FCC26DD0360FEE7114BA31E98B89061346932795F061610E63E056699A70E9B",
/* 4 */   "D5643B70DBBB87F5680E67C24C244AA7E9A5FBF936970B30F0BDA888F6EF99D2D8B979F4A240908566A1B6D1B3523B6A95E0783F4540C6FA75907824003C24FF3CE44EA66CED5CE68E1EEB832B520FD4DD54E70A5B123B406FDC55221997C14D6AB1BBC679A860CB4D5035A4F118EB07B7B5A85C5AB16A04D22D57A3E89D6FBB6D142C5F5DA45449EA714BBF8247F6613E1F54DF6307661BEDD9579A2B151666E5F0D5B077A623C981BC0E0835A7771BA4A1435664D612435D04DB4B4880904A5264AD52F667CF2891A6118B6DACCD930AE871BCF1AB96EC537906F09D0116C0540E4781FEE748E33312FACDC4BE9415E198E065FD52041F68286B1899F03FF7",
/* 5 */   "F13728253924F10B118822B066FA4385ACDEA7AF77BBD5B0B8DF17E1EE270E8D8B33C0D5D102B48838B7D45F7E2D5D84BC79D7292984B630096752031150D44A95F14D6CC41D6D65749572E9876B7E7E302590CB9E9FF068C254695E6AE77F6D0AEF4CAE9DB78A1A71351712A95AE7ADE33FA3CAF7B1573B05D07929E89D3995E35EA11CC4D9474E5B0EB276406B171423B915F5B8C165C6C1B52F008C3D683246DB27A57C1B459C08C10C9D5FCEC8BD00ECAE386C74919CEE1472B88F2D7CDFE0274A4A66044837B8DB737D75B216BB110B53DC98262C3FFCFBB2CC421E4C8F2B2F9B25B16CC3A9CD42777863FA7BA7D21ECD564E6AAD57FE90EC3CA0692E43",
/* 6 */   "C2360F042F5D1DEFE1A7860FB143672B481CE3DA8665BC62E030B31E375586BE86BB4815755F3ABFD91E679EF408BC2303D04B416C94410892B0AF422E5E197B3FD1349FEE9C6E23B7CA494D475C9959EAB6DEDCE60EDCFE0B56DC1A5257D2B5B1ADE95414C933D55EDBF0C67E3CB0B2E118B17481A29F858A9B98C570E64B006538B462A00CD8ED35129495F9B629628886581EB06DF5A226634E9F76C0F538433D4C2ADBFC5F115834710C41DDDFEB3074F4EBA1350F53CAFCF986C459ED9176BCB14384CAC4AEB416DC2D505FF9478A7748B1A662BD22D4944D124481ABF051A5C4A6C8F1EACAF45044A9EE05247AF6EFD6A41F07433BF7DC65E29D7A18BB",
/* 7 */   "D002DC7E67F5E8649AA635D4EEDB0A13C00E1E8A347A24ED04D08BEC549E99AEC44A09266D1410BCADCEA07E3D27B68425A290B3B661F2CB6F32BE0D546ABFEFB6814BD60F7F939C262301BCDC0DE3F006FEC0319CB1C345F6D218D66BC9FAAD6C9F956C7368CCC8A99255A6AAABCB28317FD0D9D039E70B618143A4A446C8FD18002317CFD23C418C05D463679A4C0A5F2EA750EF7608A6A3B865F5E65E485BAF37CB98EAB7A71AA57E51C5616FBF882557B7C0A9206EAB24F90A701C8C98C842928F6A58A124C2E472F190128EB906126C824AE36449189892108E97A084585A21CC308788D4AB5F743339B3B1B2019C5440F0F84625CC6CA3280DEBCF692F",
/* 8 */   "D39E24B58653537E380BE90F88BC009321E4C3A8B938451F3957186559BD5DEDD1EE1869CD70B2740E4F228832DEFC4B1AD671296E1AA8C6A94B8AD36C6EB9E797F74F3EF691C02174EA000176321C4725AF503BE0AEFCF9E52045D9B8CAC7937A169F64E0C5D1EAF883EE34402BF8202F3C521BDAB59D73B342BEA4EA06A5D28F6E3ADDFE596B18AD3C54DB2E0ED879AA829DD6091709BC03A87A2847228D8470D7EDCA84CA1191EAE433A1EFF551FCFA60C3DB4DD28F2D6DC8BA511BA2394F7567230CEE624A9F9131B4AB7388B94D4136DF99CBF749ED24DE7A023F4061B8992A76B32733BD922E3031C1DD53A24D3DDA204A6BC073240317E91285042AA5",
/* 9 */   "F7B4E5B46E9238E955719873B8AEEAC110C69EFDE4EA18CDE67ABAB943F560ECCDA835D57E09FC3869BB6A580E7CF2290F69C3DF3CC9A3DE2AADB95A05DA2DD99DA01FD006B7CD8676206FB3C4AA2285FF65E80E48FEC53561BE7B59320AA1DCA5C1A4621DD1317A4EB27E2A0649EB1AF69CB9F718B3AC4DFEA9061098EDF22D6879229BAE75802DA4CB1A67B71D1E63046E960D2435C07EC2FDDD682EA5E13340917D4F4BFEAC7345D6776D75194F067C9B52B885549B978625579672A00B990913971E77049612E13338E27730199DE30745407251CBB89D6E81F4C5653E04B3BA8140F9CE469BF895C44F0C646F7B7CBDAA51273AE225DDAF3C2F3EA417DB",
/* 10 */  "E60F9949830C786635561BF5A02B5FFE77A509FE8F518CEA0F1A35D95BD274B0CFE9F5FFF20B2B97526FC657E2A88A5A9B77270AA6735C7FAF804DCF12C512BFB350AF9EC7B0BBFD6B2C2E5F48E4C03D19882EBAFF10B3F0020E3E9D87E64344CCA6539BC42074F794942C8B8B1247F76C9B8C74EC43016D18172F31FA6D1DC528D3FD48AE02ADE56F97BA98DBDEAE614C1F7661E81445F224E92745D6B96DE41EFBB8C91C53D0DC8CD8625EF3116E27F0B52AECCE71AA9B9FA176342019B2CA0E7695AB813CB2B045EF265B675D9BFBFEAEE0E6B4FD877353EE27F07D385BF6B5A6A0EA2141295443BCCD924053219F8BE23C3C0AC6E09CCA374B3938566445",
};
}

bool check_expression(std::string_view expr) {
    auto all_op_cnt = 0;
    for (auto op : allowed_operators) {
        if (expr.front() == op || expr.back() == op)
            return false;

        all_op_cnt += std::count(std::begin(expr), std::end(expr), op);

        if (all_op_cnt > 2) {
            return false;
        }

        if (expr.find(op) == expr.rfind(op) - 1) {
            return false;
        }
    }

    if (all_op_cnt == 0) {
        return false;
    }

    return true;
}

void test() {
    std::vector<mpz_t> vec_mpz_512_bits(10);
    std::vector<mpz_t> vec_mpz_1024_bits(10);
    std::vector<mpz_t> vec_mpz_2048_bits(10);

    std::vector<big_int*> vec_bi_512_bits(10);
    std::vector<big_int*> vec_bi_1024_bits(10);
    std::vector<big_int*> vec_bi_2048_bits(10);

    std::vector<big_int*> gorner_vec_bi_512_bits(10);
    std::vector<big_int*> gorner_vec_bi_1024_bits(10);
    std::vector<big_int*> gorner_vec_bi_2048_bits(10);

    for (size_t i = 0; i < 10; i++) {
        mpz_init(vec_mpz_512_bits.at(i));
        mpz_init(vec_mpz_1024_bits.at(i));
        mpz_init(vec_mpz_2048_bits.at(i));

        mpz_set_str(vec_mpz_512_bits.at(i), num_512_strs.at(i).c_str(), 16);
        mpz_set_str(vec_mpz_1024_bits.at(i), num_1024_strs.at(i).c_str(), 16);
        mpz_set_str(vec_mpz_2048_bits.at(i), num_2048_strs.at(i).c_str(), 16);

        vec_bi_512_bits.at(i) = new big_int(num_512_strs.at(i));
        vec_bi_1024_bits.at(i) = new big_int(num_1024_strs.at(i));
        vec_bi_2048_bits.at(i) = new big_int(num_2048_strs.at(i));

        gorner_vec_bi_512_bits.at(i) = new big_int(num_512_strs.at(i));
        gorner_vec_bi_1024_bits.at(i) = new big_int(num_1024_strs.at(i));
        gorner_vec_bi_2048_bits.at(i) = new big_int(num_2048_strs.at(i));
    }

    auto mu_512 = vec_bi_512_bits.at(9)->getMu();
    auto mu_1024 = vec_bi_1024_bits.at(9)->getMu();
    auto mu_2048 = vec_bi_2048_bits.at(9)->getMu();


    {
        auto t1 = std::chrono::high_resolution_clock::now();
        for (size_t i = 1; i < 9; ++i) {
            vec_bi_512_bits.at(i - 1)->powModMary(vec_bi_512_bits.at(i), vec_bi_512_bits.at(9), mu_512);
        }
        auto t2 = std::chrono::high_resolution_clock::now();

        std::cout << "8 4-ary exponentations of 512 bits big_int numbers took: "
                  << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()  << " ms" << std::endl;
    }

    {
        auto t1 = std::chrono::high_resolution_clock::now();
        for (size_t i = 1; i < 9; ++i) {
            vec_bi_1024_bits.at(i - 1)->powModMary(vec_bi_1024_bits.at(i), vec_bi_1024_bits.at(9), mu_1024);
        }
        auto t2 = std::chrono::high_resolution_clock::now();

        std::cout << "8 4-ary exponentations of 1024 bits big_int numbers took: "
                  << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()  << " ms" << std::endl;
    }

    {
        auto t1 = std::chrono::high_resolution_clock::now();
        for (size_t i = 1; i < 9; ++i) {
            vec_bi_2048_bits.at(i - 1)->powModMary(vec_bi_2048_bits.at(i), vec_bi_2048_bits.at(9), mu_2048);
        }
        auto t2 = std::chrono::high_resolution_clock::now();

        std::cout << "8 4-ary exponentations of 2048 bits big_int numbers took: "
                  << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()  << " ms" << std::endl;
    }

    {
        auto t1 = std::chrono::high_resolution_clock::now();
        for (size_t i = 1; i < 9; ++i) {
            vec_bi_512_bits.at(i - 1)->powMod(vec_bi_512_bits.at(i), vec_bi_512_bits.at(9), mu_512);
        }
        auto t2 = std::chrono::high_resolution_clock::now();

        std::cout << "8 Gorner exponentations of 512 bits big_int numbers took: "
                  << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()  << " ms" << std::endl;
    }

    {
        auto t1 = std::chrono::high_resolution_clock::now();
        for (size_t i = 1; i < 9; ++i) {
            vec_bi_1024_bits.at(i - 1)->powMod(vec_bi_1024_bits.at(i), vec_bi_1024_bits.at(9), mu_1024);
        }
        auto t2 = std::chrono::high_resolution_clock::now();

        std::cout << "8 Gorner exponentations of 1024 bits big_int numbers took: "
                  << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()  << " ms" << std::endl;
    }

    {
        auto t1 = std::chrono::high_resolution_clock::now();
        for (size_t i = 1; i < 9; ++i) {
            vec_bi_2048_bits.at(i - 1)->powModMary(vec_bi_2048_bits.at(i), vec_bi_2048_bits.at(9), mu_2048);
        }
        auto t2 = std::chrono::high_resolution_clock::now();

        std::cout << "8 Gorner exponentations of 2048 bits big_int numbers took: "
                  << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()  << " ms" << std::endl;
    }

    {
        auto t1 = std::chrono::high_resolution_clock::now();
        for (size_t i = 1; i < 9; ++i) {
            mpz_powm(vec_mpz_512_bits.at(i - 1), vec_mpz_512_bits.at(i - 1), vec_mpz_512_bits.at(i), vec_mpz_512_bits.at(9));
        }
        auto t2 = std::chrono::high_resolution_clock::now();

        std::cout << "8 exponentations of 512 bits mpz_t numbers took: "
                  << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()  << " ms"  << std::endl;
    }

    {
        auto t1 = std::chrono::high_resolution_clock::now();
        for (size_t i = 1; i < 9; ++i) {
            mpz_powm(vec_mpz_1024_bits.at(i - 1), vec_mpz_1024_bits.at(i - 1), vec_mpz_1024_bits.at(i), vec_mpz_1024_bits.at(9));
        }
        auto t2 = std::chrono::high_resolution_clock::now();

        std::cout << "8 exponentations of 1024 bits mpz_t numbers took: "
                  << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()  << " ms"  << std::endl;
    }

    {
        auto t1 = std::chrono::high_resolution_clock::now();
        for (size_t i = 1; i < 9; ++i) {
            mpz_powm(vec_mpz_2048_bits.at(i - 1), vec_mpz_2048_bits.at(i - 1), vec_mpz_2048_bits.at(i), vec_mpz_2048_bits.at(9));
        }
        auto t2 = std::chrono::high_resolution_clock::now();

        std::cout << "8 exponentations of 2048 bits mpz_t numbers took: "
                  << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()  << " ms"  << std::endl;
    }
}

big_int* calculate_mod_expression(big_int* a, big_int* b, big_int* mod, char op) {
    auto mu = mod->getMu();

    switch (op) {
        case '+': {
            a->add(b);
            a->red(mod, mu);
            return a;
        }
        case '-': {
            a->sub(b);
            a->red(mod, mu);
            return a;
        }
        case '/': {
            a->div(b);
            a->red(mod, mu);
            return a;
        }
        case '%': {
            auto mu_b = b->getMu();
            a->red(b, mu_b);
            a->red(mod, mu);
            return a;
        }
        case '*': {
            std::cout << "wfw";
            a->mulMod(b, mod, mu);
            return a;
        }
        case '^': {
            a->powMod(b, mod, mu);
            return a;
        }
        default: {
            return a;
        }
    }
}

big_int* calculate_one_expression(big_int* a, big_int* b, char op) {
    switch (op) {
        case '+': {
            a->add(b);
            return a;
        }
        case '-': {
            a->sub(b);
            return a;
        }
        case '/': {
            a->div(b);
            return a;
        }
        case '%': {
            auto mu_b = b->getMu();
            a->red(b, mu_b);
            return a;
        }
        case '*': {
            a->mul(b);
            return a;
        }
        case '^': {
            a->pow(b);
            return a;
        }
        default: {
            return a;
        }
    }
}

big_int* calculate_expression(std::string_view expr) {
    std::vector<std::string> num_strs;
    auto str = std::string(expr.data());
    boost::split(num_strs, str, boost::is_any_of(allowed_operators));

    std::string ops;
    for (auto it : str) {
        if (allowed_operators.find(it) != std::string::npos) {
            ops += it;
        }
    }

    std::vector<big_int*> vec_int;
    for (auto&& num : num_strs) {
        big_int* bi = new big_int(std::move(num));
        vec_int.push_back(bi);
    }

    if (ops.size() == 2) {
        if (ops.back() == '%') {
            return calculate_mod_expression(vec_int[0], vec_int[1], vec_int[2], ops.front());
        } else {
            big_int* ret = calculate_one_expression(vec_int[0], vec_int[1], ops.front());
            return calculate_one_expression(ret, vec_int[2], ops.back());
        }
    } else {
        return calculate_one_expression(vec_int[0], vec_int[1], ops.front());
    }
}


int main(int argc, char* argv[])
{
    if (argc != 2 && argc != 3) {
        std::cout << "Wrong arguments given" << std::endl;
        return 1;
    }

    if (argc == 1) {
        if (std::string_view(argv[1]) == std::string_view("--test") ||
                std::string_view(argv[1]) == std::string_view("-t"))
        {
            std::cout << "Running tests..." << std::endl;
            test();
            std::cout << "Tests finished.";
            return 0;
        }

        if (std::string_view(argv[1]) == std::string_view("--help") ||
                std::string_view(argv[1]) == std::string_view("-h"))
        {
            std::cout << "Usage: ./lab1 [option]\n" \
                         "Possible values of [option]:\n" \
                         "--help, -h    Print help message\n" \
                         "--test, -t    Run tests\n" \
                         "--compute,-c  <expression> \n" \
                         "Allowed format of expressions:\n" \
                         "<number_in_hex_#1><operation_#1><number_in_hex_#2> or \n" \
                         "<number_in_hex_#1><operation_#1><number_in_hex_#2><operation_#2><number_in_hex_#3>\n" \
                         "Allowed values of operators: +, -, *, ^, %. \n" \
                         "Order of computations in 2 operations exprassion is " \
                         "res = number_in_hex_#1 <operation_#1><number_in_hex_#2> and then " \
                         "res<operation_#2><number_in_hex_#3>.\n" \
                         "Number must be ONLY in HEX, WITHOUT 0x!\n" \
                         "BE CAREFUL ABOUT OPERATIONS ON NEGATIVE NUMBERS!!! THERE IS NO GARANTEE IN CORRECTNESS!!!";
        } else {
            std::cout << "Wrong arguments given" << std::endl;
            return 1;
        }
    } else if (std::string_view(argv[1]) == std::string_view("--compute") ||
               std::string_view(argv[1]) == std::string_view("-c"))
    {
        if (!check_expression(argv[2])) {
            std::cout << "Invalid expression given! Aborting!" << std::endl;
            return 1;
        } else {
            auto res = calculate_expression(argv[2]);
            std::cout << std::endl << "RESULT: " << res->showNumHex() << std::endl;
        }
    } else {
        std::cout << "Wrong arguments given" << std::endl;
        return 1;
    }

    return 0;
}
