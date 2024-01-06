//
// Created by Evan Chen on 2024/1/5.
//

#ifndef FILTER_H
#define FILTER_H

#include <stdlib.h>

/*
double LCCDE_COEFFICIENTS[1025] = {
        4.20647846903578e-05,
        4.17715335258779e-05,
        4.14775283284059e-05,
        4.11825817778023e-05,
        4.08864956474276e-05,
        4.05890608785506e-05,
        4.02900576617594e-05,
        3.99892555253732e-05,
        3.96864134308443e-05,
        3.93812798751431e-05,
        3.90735930001088e-05,
        3.87630807087507e-05,
        3.84494607884802e-05,
        3.81324410412499e-05,
        3.78117194205735e-05,
        3.74869841753977e-05,
        3.71579140007936e-05,
        3.68241781954322e-05,
        3.64854368258049e-05,
        3.61413408971495e-05,
        3.57915325310334e-05,
        3.54356451495509e-05,
        3.50733036660798e-05,
        3.47041246825463e-05,
        3.43277166931396e-05,
        3.39436802944187e-05,
        3.35516084017452e-05,
        3.31510864719804e-05,
        3.27416927323752e-05,
        3.23229984155811e-05,
        3.18945680007104e-05,
        3.14559594603648e-05,
        3.10067245135547e-05,
        3.05464088844245e-05,
        3.00745525666985e-05,
        2.95906900937581e-05,
        2.90943508142592e-05,
        2.85850591731959e-05,
        2.80623349983116e-05,
        2.75256937917598e-05,
        2.69746470269107e-05,
        2.64087024501999e-05,
        2.58273643879093e-05,
        2.52301340577736e-05,
        2.46165098852949e-05,
        2.39859878246545e-05,
        2.33380616841021e-05,
        2.26722234557022e-05,
        2.19879636493156e-05,
        2.12847716306917e-05,
        2.05621359635437e-05,
        1.98195447554776e-05,
        1.90564860076432e-05,
        1.82724479679748e-05,
        1.74669194878827e-05,
        1.66393903822614e-05,
        1.57893517926719e-05,
        1.49162965535562e-05,
        1.40197195613427e-05,
        1.30991181462939e-05,
        1.21539924469500e-05,
        1.11838457870200e-05,
        1.01881850545680e-05,
        9.16652108334264e-06,
        8.11836903609531e-06,
        7.04324878973215e-06,
        5.94068532214021e-06,
        4.81020910053203e-06,
        3.65135647114670e-06,
        2.46367005014576e-06,
        1.24669911554243e-06,
        -2.16899652627925e-20,
        -1.27686351566757e-06,
        -2.58431980845564e-06,
        -3.92278901875938e-06,
        -5.29268265576173e-06,
        -6.69440320278826e-06,
        -8.12834372279814e-06,
        -9.59488746418222e-06,
        -1.10944074670403e-05,
        -1.26272661701080e-05,
        -1.41938150185066e-05,
        -1.57943940724903e-05,
        -1.74293316173606e-05,
        -1.90989437747266e-05,
        -2.08035341152813e-05,
        -2.25433932732701e-05,
        -2.43187985628270e-05,
        -2.61300135963510e-05,
        -2.79772879050992e-05,
        -2.98608565621713e-05,
        -3.17809398080593e-05,
        -3.37377426789364e-05,
        -3.57314546378627e-05,
        -3.77622492090765e-05,
        -3.98302836155497e-05,
        -4.19356984199780e-05,
        -4.40786171693777e-05,
        -4.62591460434646e-05,
        -4.84773735069833e-05,
        -5.07333699661578e-05,
        -5.30271874294374e-05,
        -5.53588591727006e-05,
        -5.77283994090911e-05,
        -6.01358029636506e-05,
        -6.25810449529134e-05,
        -6.50640804696310e-05,
        -6.75848442727885e-05,
        -7.01432504830755e-05,
        -7.27391922839738e-05,
        -7.53725416286220e-05,
        -7.80431489526139e-05,
        -8.07508428928895e-05,
        -8.34954300128740e-05,
        -8.62766945340167e-05,
        -8.90943980738842e-05,
        -9.19482793909566e-05,
        -9.48380541362765e-05,
        -9.77634146120967e-05,
        -0.000100724029537670,
        -0.000103719543822326,
        -0.000106749578345977,
        -0.000109813729747181,
        -0.000112911570218914,
        -0.000116042647312174,
        -0.000119206483747550,
        -0.000122402577234889,
        -0.000125630400301181,
        -0.000128889400126801,
        -0.000132178998390203,
        -0.000135498591121219,
        -0.000138847548563047,
        -0.000142225215043066,
        -0.000145630908852576,
        -0.000149063922135570,
        -0.000152523520786661,
        -0.000156008944358235,
        -0.000159519405976961,
        -0.000163054092269737,
        -0.000166612163299162,
        -0.000170192752508645,
        -0.000173794966677207,
        -0.000177417885884092,
        -0.000181060563483238,
        -0.000184722026087714,
        -0.000188401273564168,
        -0.000192097279037383,
        -0.000195808988904984,
        -0.000199535322862382,
        -0.000203275173937996,
        -0.000207027408538827,
        -0.000210790866506417,
        -0.000214564361183266,
        -0.000218346679489732,
        -0.000222136582011466,
        -0.000225932803097426,
        -0.000229734050968488,
        -0.000233539007836705,
        -0.000237346330035225,
        -0.000241154648158903,
        -0.000244962567215622,
        -0.000248768666788331,
        -0.000252571501207835,
        -0.000256369599736315,
        -0.000260161466761612,
        -0.000263945582002249,
        -0.000267720400723209,
        -0.000271484353962448,
        -0.000275235848768137,
        -0.000278973268446619,
        -0.000282694972821058,
        -0.000286399298500757,
        -0.000290084559161127,
        -0.000293749045834259,
        -0.000297391027210077,
        -0.000301008749948035,
        -0.000304600438999302,
        -0.000308164297939398,
        -0.000311698509311225,
        -0.000315201234978450,
        -0.000318670616489158,
        -0.000322104775449735,
        -0.000325501813908900,
        -0.000328859814751828,
        -0.000332176842104267,
        -0.000335450941746602,
        -0.000338680141537752,
        -0.000341862451848838,
        -0.000344995866006514,
        -0.000348078360745880,
        -0.000351107896672872,
        -0.000354082418736030,
        -0.000356999856707530,
        -0.000359858125673394,
        -0.000362655126532730,
        -0.000365388746505917,
        -0.000368056859651601,
        -0.000370657327392370,
        -0.000373187999049003,
        -0.000375646712383131,
        -0.000378031294148208,
        -0.000380339560648628,
        -0.000382569318306858,
        -0.000384718364238439,
        -0.000386784486834710,
        -0.000388765466353096,
        -0.000390659075514808,
        -0.000392463080109802,
        -0.000394175239608824,
        -0.000395793307782381,
        -0.000397315033326482,
        -0.000398738160494948,
        -0.000400060429738154,
        -0.000401279578347990,
        -0.000402393341108887,
        -0.000403399450954715,
        -0.000404295639631363,
        -0.000405079638364818,
        -0.000405749178534551,
        -0.000406301992352013,
        -0.000406735813544049,
        -0.000407048378041022,
        -0.000407237424669460,
        -0.000407300695849000,
        -0.000407235938293449,
        -0.000407040903715728,
        -0.000406713349536507,
        -0.000406251039596303,
        -0.000405651744870841,
        -0.000404913244189444,
        -0.000404033324956244,
        -0.000403009783873996,
        -0.000401840427670251,
        -0.000400523073825697,
        -0.000399055551304402,
        -0.000397435701285770,
        -0.000395661377897948,
        -0.000393730448952476,
        -0.000391640796679933,
        -0.000389390318466350,
        -0.000386976927590163,
        -0.000384398553959452,
        -0.000381653144849247,
        -0.000378738665638655,
        -0.000375653100547565,
        -0.000372394453372696,
        -0.000368960748222751,
        -0.000365350030252425,
        -0.000361560366395036,
        -0.000357589846093528,
        -0.000353436582029613,
        -0.000349098710850790,
        -0.000344574393895027,
        -0.000339861817912831,
        -0.000334959195786482,
        -0.000329864767246184,
        -0.000324576799582881,
        -0.000319093588357507,
        -0.000313413458106411,
        -0.000307534763042732,
        -0.000301455887753465,
        -0.000295175247891987,
        -0.000288691290865788,
        -0.000282002496519194,
        -0.000275107377810799,
        -0.000268004481485405,
        -0.000260692388740215,
        -0.000253169715885037,
        -0.000245435114996274,
        -0.000237487274564455,
        -0.000229324920135076,
        -0.000220946814942526,
        -0.000212351760536849,
        -0.000203538597403127,
        -0.000194506205573253,
        -0.000185253505229863,
        -0.000175779457302196,
        -0.000166083064053682,
        -0.000156163369661006,
        -0.000146019460784453,
        -0.000135650467129303,
        -0.000125055561998063,
        -0.000114233962833329,
        -0.000103184931751061,
        -9.19077760640607e-05,
        -8.04018487954531e-05,
        -6.86665491819658e-05,
        -5.67013231667971e-05,
        -4.45056638818882e-05,
        -3.20791121193948e-05,
        -1.94212567921626e-05,
        -6.53173538302853e-06,
        6.58976561724963e-06,
        1.99435102836203e-05,
        3.35297128420886e-05,
        4.73485372669902e-05,
        6.14000968903411e-05,
        7.56844540234485e-05,
        9.02016195909483e-05,
        0.000104951552777431,
        0.000119934160686817,
        0.000135149298014637,
        0.000150596766733390,
        0.000166276315791092,
        0.000182187640823196,
        0.000198330383878017,
        0.000214704133155791,
        0.000231308422761509,
        0.000248142732471665,
        0.000265206487515030,
        0.000282499058367592,
        0.000300019760561763,
        0.000317767854509983,
        0.000335742545342823,
        0.000353942982761701,
        0.000372368260906296,
        0.000391017418236786,
        0.000409889437430975,
        0.000428983245296414,
        0.000448297712697597,
        0.000467831654498312,
        0.000487583829519225,
        0.000507552940510755,
        0.000527737634141328,
        0.000548136501001054,
        0.000568748075620893,
        0.000589570836507354,
        0.000610603206192785,
        0.000631843551301294,
        0.000653290182630327,
        0.000674941355247955,
        0.000696795268605889,
        0.000718850066668242,
        0.000741103838056061,
        0.000763554616207657,
        0.000786200379554709,
        0.000809039051714179,
        0.000832068501696023,
        0.000855286544126686,
        0.000878690939488380,
        0.000902279394374137,
        0.000926049561758584,
        0.000949999041284461,
        0.000974125379564806,
        0.000998426070500805,
        0.00102289855561525,
        0.00104754022440157,
        0.00107234841468835,
        0.00109732041301936,
        0.00112245345504892,
        0.00114774472595270,
        0.00117319136085363,
        0.00119879044526318,
        0.00122453901553761,
        0.00125043405934931,
        0.00127647251617306,
        0.00130265127778714,
        0.00132896718878918,
        0.00135541704712663,
        0.00138199760464180,
        0.00140870556763125,
        0.00143553759741953,
        0.00146249031094710,
        0.00148956028137227,
        0.00151674403868702,
        0.00154403807034671,
        0.00157143882191327,
        0.00159894269771204,
        0.00162654606150183,
        0.00165424523715820,
        0.00168203650936980,
        0.00170991612434753,
        0.00173788029054642,
        0.00176592517939999,
        0.00179404692606700,
        0.00182224163019037,
        0.00185050535666803,
        0.00187883413643558,
        0.00190722396726059,
        0.00193567081454824,
        0.00196417061215820,
        0.00199271926323250,
        0.00202131264103416,
        0.00204994658979643,
        0.00207861692558240,
        0.00210731943715469,
        0.00213604988685511,
        0.00216480401149399,
        0.00219357752324902,
        0.00222236611057321,
        0.00225116543911196,
        0.00227997115262883,
        0.00230877887393979,
        0.00233758420585580,
        0.00236638273213335,
        0.00239517001843281,
        0.00242394161328426,
        0.00245269304906055,
        0.00248141984295743,
        0.00251011749798033,
        0.00253878150393762,
        0.00256740733844016,
        0.00259599046790662,
        0.00262452634857456,
        0.00265301042751691,
        0.00268143814366346,
        0.00270980492882729,
        0.00273810620873562,
        0.00276633740406506,
        0.00279449393148073,
        0.00282257120467911,
        0.00285056463543438,
        0.00287846963464769,
        0.00290628161339948,
        0.00293399598400415,
        0.00296160816106711,
        0.00298911356254369,
        0.00301650761079977,
        0.00304378573367370,
        0.00307094336553936,
        0.00309797594836996,
        0.00312487893280224,
        0.00315164777920096,
        0.00317827795872317,
        0.00320476495438206,
        0.00323110426211012,
        0.00325729139182125,
        0.00328332186847152,
        0.00330919123311832,
        0.00333489504397758,
        0.00336042887747877,
        0.00338578832931732,
        0.00341096901550426,
        0.00343596657341273,
        0.00346077666282104,
        0.00348539496695202,
        0.00350981719350830,
        0.00353403907570339,
        0.00355805637328801,
        0.00358186487357158,
        0.00360546039243853,
        0.00362883877535909,
        0.00365199589839424,
        0.00367492766919473,
        0.00369763002799356,
        0.00372009894859201,
        0.00374233043933853,
        0.00376432054410062,
        0.00378606534322905,
        0.00380756095451440,
        0.00382880353413551,
        0.00384978927759967,
        0.00387051442067409,
        0.00389097524030861,
        0.00391116805554924,
        0.00393108922844229,
        0.00395073516492883,
        0.00397010231572926,
        0.00398918717721763,
        0.00400798629228563,
        0.00402649625119576,
        0.00404471369242367,
        0.00406263530348929,
        0.00408025782177646,
        0.00409757803534100,
        0.00411459278370683,
        0.00413129895864992,
        0.00414769350496995,
        0.00416377342124929,
        0.00417953576059929,
        0.00419497763139336,
        0.00421009619798701,
        0.00422488868142425,
        0.00423935236013045,
        0.00425348457059124,
        0.00426728270801742,
        0.00428074422699554,
        0.00429386664212408,
        0.00430664752863492,
        0.00431908452300006,
        0.00433117532352330,
        0.00434291769091669,
        0.00435430944886176,
        0.00436534848455508,
        0.00437603274923828,
        0.00438636025871214,
        0.00439632909383477,
        0.00440593740100362,
        0.00441518339262121,
        0.00442406534754450,
        0.00443258161151764,
        0.00444073059758814,
        0.00444851078650616,
        0.00445592072710697,
        0.00446295903667632,
        0.00446962440129870,
        0.00447591557618838,
        0.00448183138600311,
        0.00448737072514038,
        0.00449253255801617,
        0.00449731591932613,
        0.00450171991428902,
        0.00450574371887253,
        0.00450938658000111,
        0.00451264781574611,
        0.00451552681549785,
        0.00451802304011979,
        0.00452013602208462,
        0.00452186536559234,
        0.00452321074667018,
        0.00452417191325445,
        0.00452474868525415,
        0.00452494095459648,
        0.00452474868525415,
        0.00452417191325445,
        0.00452321074667018,
        0.00452186536559234,
        0.00452013602208462,
        0.00451802304011979,
        0.00451552681549785,
        0.00451264781574611,
        0.00450938658000111,
        0.00450574371887253,
        0.00450171991428902,
        0.00449731591932613,
        0.00449253255801617,
        0.00448737072514038,
        0.00448183138600311,
        0.00447591557618838,
        0.00446962440129870,
        0.00446295903667632,
        0.00445592072710697,
        0.00444851078650616,
        0.00444073059758814,
        0.00443258161151764,
        0.00442406534754450,
        0.00441518339262121,
        0.00440593740100362,
        0.00439632909383477,
        0.00438636025871214,
        0.00437603274923828,
        0.00436534848455508,
        0.00435430944886176,
        0.00434291769091669,
        0.00433117532352330,
        0.00431908452300006,
        0.00430664752863492,
        0.00429386664212408,
        0.00428074422699554,
        0.00426728270801742,
        0.00425348457059124,
        0.00423935236013045,
        0.00422488868142425,
        0.00421009619798701,
        0.00419497763139336,
        0.00417953576059929,
        0.00416377342124929,
        0.00414769350496995,
        0.00413129895864992,
        0.00411459278370683,
        0.00409757803534100,
        0.00408025782177646,
        0.00406263530348929,
        0.00404471369242367,
        0.00402649625119576,
        0.00400798629228563,
        0.00398918717721763,
        0.00397010231572926,
        0.00395073516492883,
        0.00393108922844229,
        0.00391116805554924,
        0.00389097524030861,
        0.00387051442067409,
        0.00384978927759967,
        0.00382880353413551,
        0.00380756095451440,
        0.00378606534322905,
        0.00376432054410062,
        0.00374233043933853,
        0.00372009894859201,
        0.00369763002799356,
        0.00367492766919473,
        0.00365199589839424,
        0.00362883877535909,
        0.00360546039243853,
        0.00358186487357158,
        0.00355805637328801,
        0.00353403907570339,
        0.00350981719350830,
        0.00348539496695202,
        0.00346077666282104,
        0.00343596657341273,
        0.00341096901550426,
        0.00338578832931732,
        0.00336042887747877,
        0.00333489504397758,
        0.00330919123311832,
        0.00328332186847152,
        0.00325729139182125,
        0.00323110426211012,
        0.00320476495438206,
        0.00317827795872317,
        0.00315164777920096,
        0.00312487893280224,
        0.00309797594836996,
        0.00307094336553936,
        0.00304378573367370,
        0.00301650761079977,
        0.00298911356254369,
        0.00296160816106711,
        0.00293399598400415,
        0.00290628161339948,
        0.00287846963464769,
        0.00285056463543438,
        0.00282257120467911,
        0.00279449393148073,
        0.00276633740406506,
        0.00273810620873562,
        0.00270980492882729,
        0.00268143814366346,
        0.00265301042751691,
        0.00262452634857456,
        0.00259599046790662,
        0.00256740733844016,
        0.00253878150393762,
        0.00251011749798033,
        0.00248141984295743,
        0.00245269304906055,
        0.00242394161328426,
        0.00239517001843281,
        0.00236638273213335,
        0.00233758420585580,
        0.00230877887393979,
        0.00227997115262883,
        0.00225116543911196,
        0.00222236611057321,
        0.00219357752324902,
        0.00216480401149399,
        0.00213604988685511,
        0.00210731943715469,
        0.00207861692558240,
        0.00204994658979643,
        0.00202131264103416,
        0.00199271926323250,
        0.00196417061215820,
        0.00193567081454824,
        0.00190722396726059,
        0.00187883413643558,
        0.00185050535666803,
        0.00182224163019037,
        0.00179404692606700,
        0.00176592517939999,
        0.00173788029054642,
        0.00170991612434753,
        0.00168203650936980,
        0.00165424523715820,
        0.00162654606150183,
        0.00159894269771204,
        0.00157143882191327,
        0.00154403807034671,
        0.00151674403868702,
        0.00148956028137227,
        0.00146249031094710,
        0.00143553759741953,
        0.00140870556763125,
        0.00138199760464180,
        0.00135541704712663,
        0.00132896718878918,
        0.00130265127778714,
        0.00127647251617306,
        0.00125043405934931,
        0.00122453901553761,
        0.00119879044526318,
        0.00117319136085363,
        0.00114774472595270,
        0.00112245345504892,
        0.00109732041301936,
        0.00107234841468835,
        0.00104754022440157,
        0.00102289855561525,
        0.000998426070500805,
        0.000974125379564806,
        0.000949999041284461,
        0.000926049561758584,
        0.000902279394374137,
        0.000878690939488380,
        0.000855286544126686,
        0.000832068501696023,
        0.000809039051714179,
        0.000786200379554709,
        0.000763554616207657,
        0.000741103838056061,
        0.000718850066668242,
        0.000696795268605889,
        0.000674941355247955,
        0.000653290182630327,
        0.000631843551301294,
        0.000610603206192785,
        0.000589570836507354,
        0.000568748075620893,
        0.000548136501001054,
        0.000527737634141328,
        0.000507552940510755,
        0.000487583829519225,
        0.000467831654498312,
        0.000448297712697597,
        0.000428983245296414,
        0.000409889437430975,
        0.000391017418236786,
        0.000372368260906296,
        0.000353942982761701,
        0.000335742545342823,
        0.000317767854509983,
        0.000300019760561763,
        0.000282499058367592,
        0.000265206487515030,
        0.000248142732471665,
        0.000231308422761509,
        0.000214704133155791,
        0.000198330383878017,
        0.000182187640823196,
        0.000166276315791092,
        0.000150596766733390,
        0.000135149298014637,
        0.000119934160686817,
        0.000104951552777431,
        9.02016195909483e-05,
        7.56844540234485e-05,
        6.14000968903411e-05,
        4.73485372669902e-05,
        3.35297128420886e-05,
        1.99435102836203e-05,
        6.58976561724963e-06,
        -6.53173538302853e-06,
        -1.94212567921626e-05,
        -3.20791121193948e-05,
        -4.45056638818882e-05,
        -5.67013231667971e-05,
        -6.86665491819658e-05,
        -8.04018487954531e-05,
        -9.19077760640607e-05,
        -0.000103184931751061,
        -0.000114233962833329,
        -0.000125055561998063,
        -0.000135650467129303,
        -0.000146019460784453,
        -0.000156163369661006,
        -0.000166083064053682,
        -0.000175779457302196,
        -0.000185253505229863,
        -0.000194506205573253,
        -0.000203538597403127,
        -0.000212351760536849,
        -0.000220946814942526,
        -0.000229324920135076,
        -0.000237487274564455,
        -0.000245435114996274,
        -0.000253169715885037,
        -0.000260692388740215,
        -0.000268004481485405,
        -0.000275107377810799,
        -0.000282002496519194,
        -0.000288691290865788,
        -0.000295175247891987,
        -0.000301455887753465,
        -0.000307534763042732,
        -0.000313413458106411,
        -0.000319093588357507,
        -0.000324576799582881,
        -0.000329864767246184,
        -0.000334959195786482,
        -0.000339861817912831,
        -0.000344574393895027,
        -0.000349098710850790,
        -0.000353436582029613,
        -0.000357589846093528,
        -0.000361560366395036,
        -0.000365350030252425,
        -0.000368960748222751,
        -0.000372394453372696,
        -0.000375653100547565,
        -0.000378738665638655,
        -0.000381653144849247,
        -0.000384398553959452,
        -0.000386976927590163,
        -0.000389390318466350,
        -0.000391640796679933,
        -0.000393730448952476,
        -0.000395661377897948,
        -0.000397435701285770,
        -0.000399055551304402,
        -0.000400523073825697,
        -0.000401840427670251,
        -0.000403009783873996,
        -0.000404033324956244,
        -0.000404913244189444,
        -0.000405651744870841,
        -0.000406251039596303,
        -0.000406713349536507,
        -0.000407040903715728,
        -0.000407235938293449,
        -0.000407300695849000,
        -0.000407237424669460,
        -0.000407048378041022,
        -0.000406735813544049,
        -0.000406301992352013,
        -0.000405749178534551,
        -0.000405079638364818,
        -0.000404295639631363,
        -0.000403399450954715,
        -0.000402393341108887,
        -0.000401279578347990,
        -0.000400060429738154,
        -0.000398738160494948,
        -0.000397315033326482,
        -0.000395793307782381,
        -0.000394175239608824,
        -0.000392463080109802,
        -0.000390659075514808,
        -0.000388765466353096,
        -0.000386784486834710,
        -0.000384718364238439,
        -0.000382569318306858,
        -0.000380339560648628,
        -0.000378031294148208,
        -0.000375646712383131,
        -0.000373187999049003,
        -0.000370657327392370,
        -0.000368056859651601,
        -0.000365388746505917,
        -0.000362655126532730,
        -0.000359858125673394,
        -0.000356999856707530,
        -0.000354082418736030,
        -0.000351107896672872,
        -0.000348078360745880,
        -0.000344995866006514,
        -0.000341862451848838,
        -0.000338680141537752,
        -0.000335450941746602,
        -0.000332176842104267,
        -0.000328859814751828,
        -0.000325501813908900,
        -0.000322104775449735,
        -0.000318670616489158,
        -0.000315201234978450,
        -0.000311698509311225,
        -0.000308164297939398,
        -0.000304600438999302,
        -0.000301008749948035,
        -0.000297391027210077,
        -0.000293749045834259,
        -0.000290084559161127,
        -0.000286399298500757,
        -0.000282694972821058,
        -0.000278973268446619,
        -0.000275235848768137,
        -0.000271484353962448,
        -0.000267720400723209,
        -0.000263945582002249,
        -0.000260161466761612,
        -0.000256369599736315,
        -0.000252571501207835,
        -0.000248768666788331,
        -0.000244962567215622,
        -0.000241154648158903,
        -0.000237346330035225,
        -0.000233539007836705,
        -0.000229734050968488,
        -0.000225932803097426,
        -0.000222136582011466,
        -0.000218346679489732,
        -0.000214564361183266,
        -0.000210790866506417,
        -0.000207027408538827,
        -0.000203275173937996,
        -0.000199535322862382,
        -0.000195808988904984,
        -0.000192097279037383,
        -0.000188401273564168,
        -0.000184722026087714,
        -0.000181060563483238,
        -0.000177417885884092,
        -0.000173794966677207,
        -0.000170192752508645,
        -0.000166612163299162,
        -0.000163054092269737,
        -0.000159519405976961,
        -0.000156008944358235,
        -0.000152523520786661,
        -0.000149063922135570,
        -0.000145630908852576,
        -0.000142225215043066,
        -0.000138847548563047,
        -0.000135498591121219,
        -0.000132178998390203,
        -0.000128889400126801,
        -0.000125630400301181,
        -0.000122402577234889,
        -0.000119206483747550,
        -0.000116042647312174,
        -0.000112911570218914,
        -0.000109813729747181,
        -0.000106749578345977,
        -0.000103719543822326,
        -0.000100724029537670,
        -9.77634146120967e-05,
        -9.48380541362765e-05,
        -9.19482793909566e-05,
        -8.90943980738842e-05,
        -8.62766945340167e-05,
        -8.34954300128740e-05,
        -8.07508428928895e-05,
        -7.80431489526139e-05,
        -7.53725416286220e-05,
        -7.27391922839738e-05,
        -7.01432504830755e-05,
        -6.75848442727885e-05,
        -6.50640804696310e-05,
        -6.25810449529134e-05,
        -6.01358029636506e-05,
        -5.77283994090911e-05,
        -5.53588591727006e-05,
        -5.30271874294374e-05,
        -5.07333699661578e-05,
        -4.84773735069833e-05,
        -4.62591460434646e-05,
        -4.40786171693777e-05,
        -4.19356984199780e-05,
        -3.98302836155497e-05,
        -3.77622492090765e-05,
        -3.57314546378627e-05,
        -3.37377426789364e-05,
        -3.17809398080593e-05,
        -2.98608565621713e-05,
        -2.79772879050992e-05,
        -2.61300135963510e-05,
        -2.43187985628270e-05,
        -2.25433932732701e-05,
        -2.08035341152813e-05,
        -1.90989437747266e-05,
        -1.74293316173606e-05,
        -1.57943940724903e-05,
        -1.41938150185066e-05,
        -1.26272661701080e-05,
        -1.10944074670403e-05,
        -9.59488746418222e-06,
        -8.12834372279814e-06,
        -6.69440320278826e-06,
        -5.29268265576173e-06,
        -3.92278901875938e-06,
        -2.58431980845564e-06,
        -1.27686351566757e-06,
        -2.16899652627925e-20,
        1.24669911554243e-06,
        2.46367005014576e-06,
        3.65135647114670e-06,
        4.81020910053203e-06,
        5.94068532214021e-06,
        7.04324878973215e-06,
        8.11836903609531e-06,
        9.16652108334264e-06,
        1.01881850545680e-05,
        1.11838457870200e-05,
        1.21539924469500e-05,
        1.30991181462939e-05,
        1.40197195613427e-05,
        1.49162965535562e-05,
        1.57893517926719e-05,
        1.66393903822614e-05,
        1.74669194878827e-05,
        1.82724479679748e-05,
        1.90564860076432e-05,
        1.98195447554776e-05,
        2.05621359635437e-05,
        2.12847716306917e-05,
        2.19879636493156e-05,
        2.26722234557022e-05,
        2.33380616841021e-05,
        2.39859878246545e-05,
        2.46165098852949e-05,
        2.52301340577736e-05,
        2.58273643879093e-05,
        2.64087024501999e-05,
        2.69746470269107e-05,
        2.75256937917598e-05,
        2.80623349983116e-05,
        2.85850591731959e-05,
        2.90943508142592e-05,
        2.95906900937581e-05,
        3.00745525666985e-05,
        3.05464088844245e-05,
        3.10067245135547e-05,
        3.14559594603648e-05,
        3.18945680007104e-05,
        3.23229984155811e-05,
        3.27416927323752e-05,
        3.31510864719804e-05,
        3.35516084017452e-05,
        3.39436802944187e-05,
        3.43277166931396e-05,
        3.47041246825463e-05,
        3.50733036660798e-05,
        3.54356451495509e-05,
        3.57915325310334e-05,
        3.61413408971495e-05,
        3.64854368258049e-05,
        3.68241781954322e-05,
        3.71579140007936e-05,
        3.74869841753977e-05,
        3.78117194205735e-05,
        3.81324410412499e-05,
        3.84494607884802e-05,
        3.87630807087507e-05,
        3.90735930001088e-05,
        3.93812798751431e-05,
        3.96864134308443e-05,
        3.99892555253732e-05,
        4.02900576617594e-05,
        4.05890608785506e-05,
        4.08864956474276e-05,
        4.11825817778023e-05,
        4.14775283284059e-05,
        4.17715335258779e-05,
        4.20647846903578e-05
};
*/

size_t get_order_by_M(int M);
double* hamming_window(size_t order);
double* create_lowpass_filter(int cutoff_frequency, int sample_rate, size_t order);

void convolve(double* output,
              double* x, size_t x_len,
              double* h, size_t h_len);

void convolve_by_frame(double* output, double* previous, double* buffer,
                       double* x, size_t x_len,
                       double* h, size_t h_len);

#endif //FILTER_H
