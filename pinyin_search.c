#include "pinyin_search.h"

#include <stdio.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
    const char* py;
    const char* py_mb;
}py_index_t;
//字数有7451个
//修复必须全拼才能打出字的问题，现在只需要输一个字母即可出现候选字
const char pinyin_mb_a[] = { "啊阿呵吖" };
const char pinyin_mb_ai[] = { "爱矮挨哎碍癌艾唉哀蔼隘埃皑呆嗌嫒瑷暧捱砹嗳锿霭乃剀呃奇阂崖" };
const char pinyin_mb_an[] = { "按安暗岸俺案鞍氨胺厂广庵揞犴铵桉谙鹌埯黯干盒" };
const char pinyin_mb_ang[] = { "昂肮盎仰" };
const char pinyin_mb_ao[] = { "袄凹傲奥熬懊敖翱澳嚣拗媪廒骜嗷坳遨聱螯獒鏊鳌鏖岙噢" };
const char pinyin_mb_ba[] = { "把八吧爸拔罢跋巴芭扒坝霸叭靶笆疤耙捌粑茇岜鲅钯魃菝灞杷伯" };
const char pinyin_mb_bai[] = { "百白摆败柏拜佰伯稗捭呗薭掰" };
const char pinyin_mb_ban[] = { "半办班般拌搬版斑板伴扳扮瓣颁绊癍坂钣舨阪瘢" };
const char pinyin_mb_bang[] = { "帮棒绑磅镑邦榜蚌傍梆膀谤浜蒡彭" };
const char pinyin_mb_bao[] = { "包抱报饱保暴薄宝爆剥豹刨雹褒堡苞胞鲍炮瀑龅孢煲褓鸨趵曝簿葆勹" };
const char pinyin_mb_bei[] = { "被北倍杯背悲备碑卑贝辈钡焙狈惫臂褙悖蓓鹎鐾呗邶鞴孛陂碚" };
const char pinyin_mb_ben[] = { "本奔苯笨夯锛贲畚坌体" };
const char pinyin_mb_beng[] = { "蹦绷甭崩迸蚌泵甏嘣堋" };
const char pinyin_mb_bi[] = { "比笔闭鼻碧必避逼毕臂彼鄙壁蓖币弊辟蔽毙庇敝陛毖痹秘泌秕薜荸芘萆匕裨畀俾嬖狴筚箅篦舭荜襞庳铋跸吡愎贲滗濞璧哔髀弼妣婢纰佛拂" };
const char pinyin_mb_bian[] = { "边变便遍编辩扁贬鞭卞辨辫忭砭匾汴碥蝙褊鳊笾苄窆弁缏煸" };
const char pinyin_mb_biao[] = { "表标彪膘杓婊飑飙鳔瘭飚镳裱骠镖髟灬" };
const char pinyin_mb_bie[] = { "别憋鳖瘪蹩" };
const char pinyin_mb_bin[] = { "宾濒摈彬斌滨膑殡缤髌傧槟玢鬓镔豳份频" };
const char pinyin_mb_bing[] = { "并病兵冰丙饼屏秉柄炳摒槟禀邴冫枋绠" };
const char pinyin_mb_bo[] = { "拨波播泊博伯驳玻剥薄勃菠钵搏脖帛般柏舶渤铂箔膊魄卜礴跛檗亳鹁踣啵蕃簸钹饽擘佛擗簿趵" };
const char pinyin_mb_bu[] = { "不步补布部捕卜簿哺堡埠怖埔瓿逋晡钸钚醭卟" };
const char pinyin_mb_ca[] = { "擦拆礤嚓" };
const char pinyin_mb_cai[] = { "猜才材财裁采彩睬踩菜蔡" };
const char pinyin_mb_can[] = { "蚕残掺参惨惭餐灿骖璨孱黪粲" };
const char pinyin_mb_cang[] = { "藏仓沧舱苍伧臧" };
const char pinyin_mb_cao[] = { "草操曹槽糙嘈艚螬漕屮" };
const char pinyin_mb_ce[] = { "册侧策测厕恻" };
const char pinyin_mb_cen[] = { "参岑涔" };
const char pinyin_mb_ceng[] = { "曾层蹭噌" };
const char pinyin_mb_cha[] = { "查插叉茶差岔搽察茬碴刹诧楂槎镲衩汊馇檫姹杈锸嚓猹苴喳" };
const char pinyin_mb_chai[] = { "菜柴拆差豺钗瘥虿侪" };
const char pinyin_mb_chan[] = { "产缠掺搀阐颤铲谗蝉单馋觇婵蒇谄冁廛孱蟾羼镡忏潺禅骣躔澶崭掸" };
const char pinyin_mb_chang[] = { "长唱常场厂尝肠畅昌敞倡偿猖裳鲳氅菖惝嫦徜鬯阊怅伥昶苌娼倘淌" };
const char pinyin_mb_chao[] = { "朝抄超吵潮巢炒嘲剿绰钞怊焯耖晁" };
const char pinyin_mb_che[] = { "车撤扯掣彻尺澈坼砗屮" };
const char pinyin_mb_chen[] = { "趁称辰臣尘晨沉陈衬橙忱郴榇抻谌碜谶宸龀嗔伧琛沈肜" };
const char pinyin_mb_cheng[] = { "成乘盛撑称城程承呈秤诚惩逞骋澄橙塍柽埕铖噌铛酲晟裎枨蛏丞瞠净抢" };
const char pinyin_mb_chi[] = { "吃尺迟池翅痴赤齿耻持斥侈弛驰炽匙踟坻茌墀饬媸豉褫敕哧瘛蚩啻鸱眵螭篪魑叱彳笞嗤傺眙" };
const char pinyin_mb_chong[] = { "冲重虫充宠崇涌种艟忡舂铳憧茺" };
const char pinyin_mb_chou[] = { "抽愁臭仇丑稠绸酬筹踌畴瞅惆俦帱瘳雠" };
const char pinyin_mb_chu[] = { "出处初锄除触橱楚础储畜滁矗搐躇厨雏楮杵刍怵绌亍憷蹰黜蜍樗助褚" };
const char pinyin_mb_chuai[] = { "揣膪啜嘬搋踹" };
const char pinyin_mb_chuan[] = { "穿船传串川喘椽氚遄钏舡舛巛" };
const char pinyin_mb_chuang[] = { "窗床闯创疮幢怆" };
const char pinyin_mb_chui[] = { "吹垂炊锤捶椎槌棰陲" };
const char pinyin_mb_chun[] = { "春唇纯蠢醇淳椿蝽莼鹑朐肫" };
const char pinyin_mb_chuo[] = { "戳绰踔啜龊辍淖辶" };
const char pinyin_mb_ci[] = { "次此词瓷慈雌磁辞刺茨伺疵赐差兹呲鹚祠糍粢" };
const char pinyin_mb_cong[] = { "从丛葱匆聪囱琮枞淙璁骢苁" };
const char pinyin_mb_cou[] = { "凑楱辏腠" };
const char pinyin_mb_cu[] = { "粗醋簇促卒徂猝蔟蹙酢殂蹴趋趣" };
const char pinyin_mb_cuan[] = { "窜蹿篡攒汆爨镩撺" };
const char pinyin_mb_cui[] = { "催脆摧翠崔淬衰瘁粹璀啐悴萃毳榱" };
const char pinyin_mb_cun[] = { "村寸存蹲忖皴" };
const char pinyin_mb_cuo[] = { "错撮搓挫措磋嵯厝鹾脞痤蹉瘥锉矬" };
const char pinyin_mb_da[] = { "大答达打搭瘩塔笪耷哒褡疸怛靼妲沓嗒鞑" };
const char pinyin_mb_dai[] = { "带代呆戴待袋逮歹贷怠傣大殆呔玳迨岱甙黛骀绐埭隶" };
const char pinyin_mb_dan[] = { "但单蛋担弹掸胆淡丹耽旦氮诞郸惮石疸澹瘅萏殚眈聃箪赕儋啖膻" };
const char pinyin_mb_dang[] = { "当党挡档荡谠铛宕菪凼裆砀" };
const char pinyin_mb_dao[] = { "到道倒刀岛盗稻捣悼导蹈祷帱纛忉焘氘叨刂" };
const char pinyin_mb_de[] = { "的地得德底锝" };
const char pinyin_mb_dei[] = { "得" };
const char pinyin_mb_deng[] = { "等灯邓登澄瞪凳蹬磴镫噔嶝戥簦" };
const char pinyin_mb_di[] = { "地第底低敌抵滴帝递嫡弟缔堤的涤提笛迪狄翟蒂觌邸谛诋嘀柢骶羝氐棣睇娣荻碲镝坻籴砥" };
const char pinyin_mb_dia[] = { "嗲" };
const char pinyin_mb_dian[] = { "点电店殿淀掂颠垫碘惦奠典佃靛滇甸踮钿坫阽癫簟玷巅癜" };
const char pinyin_mb_diao[] = { "掉钓叼吊雕调刁碉凋鸟铞铫鲷貂" };
const char pinyin_mb_die[] = { "爹跌叠碟蝶迭谍牒堞瓞揲蹀耋鲽垤喋佚" };
const char pinyin_mb_ding[] = { "顶定盯订叮丁钉鼎锭町玎铤腚碇疔仃耵酊啶" };
const char pinyin_mb_diu[] = { "丢铥" };
const char pinyin_mb_dong[] = { "动东懂洞冻冬董栋侗恫峒鸫垌胨胴硐氡岽咚" };
const char pinyin_mb_dou[] = { "都斗豆逗陡抖痘兜读蚪窦篼蔸渎钭" };
const char pinyin_mb_du[] = { "读度毒渡堵独肚镀赌睹杜督都犊妒顿蠹笃嘟渎椟牍黩髑芏竺" };
const char pinyin_mb_duan[] = { "段短断端锻缎椴煅簖" };
const char pinyin_mb_dui[] = { "对队堆兑敦镦碓怼憝" };
const char pinyin_mb_dun[] = { "吨顿蹲墩敦钝盾囤遁不趸沌盹镦礅炖砘" };
const char pinyin_mb_duo[] = { "多朵夺舵剁垛跺惰堕掇哆驮度躲踱沲咄铎裰哚缍隋" };
const char pinyin_mb_e[] = { "饿哦额鹅蛾扼俄讹阿遏峨娥恶厄鄂锇谔垩锷阏萼苊轭婀莪鳄颚腭愕呃噩鹗屙" };
const char pinyin_mb_ei[] = { "诶" };
const char pinyin_mb_en[] = { "恩嗯摁蒽" };
const char pinyin_mb_er[] = { "而二耳儿饵尔贰洱珥鲕鸸佴迩铒" };
const char pinyin_mb_fa[] = { "发法罚伐乏筏阀珐垡砝" };
const char pinyin_mb_fan[] = { "反饭翻番犯凡帆返泛繁烦贩范樊藩矾钒燔蘩畈蕃蹯梵幡拚袢" };
const char pinyin_mb_fang[] = { "放房防纺芳方访仿坊妨肪钫彷邡枋舫鲂匚" };
const char pinyin_mb_fei[] = { "非飞肥费肺废匪吠沸菲诽啡篚蜚腓扉妃斐狒芾悱镄霏翡榧淝鲱绯痱怫砩" };
const char pinyin_mb_fen[] = { "分份芬粉坟奋愤纷忿粪酚焚吩氛汾棼瀵鲼玢偾鼢" };
const char pinyin_mb_feng[] = { "风封逢缝蜂丰枫疯冯奉讽凤峰锋烽砜俸酆葑沣唪" };
const char pinyin_mb_fo[] = { "佛" };
const char pinyin_mb_fou[] = { "否缶不" };
const char pinyin_mb_fu[] = { "副幅扶浮富福负伏付复服附俯芙斧赴缚拂夫父符孵敷赋辅府腐腹妇抚覆辐肤氟佛俘傅讣弗涪袱市甫釜脯腑阜咐黼砩苻趺跗蚨芾鲋幞宓茯滏蜉拊呒菔蝠鳆蝮绂绋赙罘稃匐麸凫桴莩孚馥驸怫祓呋郛艴黻阝" };
const char pinyin_mb_ga[] = { "噶胳夹嘎咖轧钆伽旮尬尕尜呷" };
const char pinyin_mb_gai[] = { "该改盖概钙芥溉戤垓丐陔赅" };
const char pinyin_mb_gan[] = { "赶干感敢竿甘肝柑杆赣秆旰酐矸疳泔苷擀绀橄澉淦尴坩乾" };
const char pinyin_mb_gang[] = { "刚钢纲港缸岗杠冈肛扛筻罡戆" };
const char pinyin_mb_gao[] = { "高搞告稿膏篙羔糕镐皋郜诰杲缟睾槔锆槁藁" };
const char pinyin_mb_ge[] = { "个各歌割哥搁格阁隔革咯胳葛蛤戈鸽疙盖屹合铬硌骼颌袼塥虼圪镉仡舸鬲嗝膈搿纥哿" };
const char pinyin_mb_gei[] = { "给" };
const char pinyin_mb_gen[] = { "跟根哏茛亘艮" };
const char pinyin_mb_geng[] = { "更耕颈梗耿庚羹埂赓鲠哽绠" };
const char pinyin_mb_gong[] = { "工公功共弓攻宫供恭拱贡躬巩汞龚红肱觥珙蚣" };
const char pinyin_mb_gou[] = { "够沟狗钩勾购构苟垢句岣彀枸鞲觏缑笱诟遘媾篝佝" };
const char pinyin_mb_gu[] = { "古股鼓谷故孤箍姑顾固雇估咕骨辜沽蛊贾菇梏鸪汩轱崮菰鹄鹘钴臌酤呱鲴诂牯瞽毂锢牿痼觚蛄罟嘏" };
const char pinyin_mb_gua[] = { "挂刮瓜寡剐褂卦呱胍鸹栝诖括" };
const char pinyin_mb_guai[] = { "怪拐乖掴" };
const char pinyin_mb_guan[] = { "关管官观馆惯罐灌冠贯棺纶盥矜莞掼涫鳏鹳倌" };
const char pinyin_mb_guang[] = { "光广逛桄犷咣胱潢" };
const char pinyin_mb_gui[] = { "归贵鬼跪轨规硅桂柜龟诡闺瑰圭刽傀癸炔庋宄桧刿鳜鲑皈匦妫晷簋炅匮" };
const char pinyin_mb_gun[] = { "滚棍辊鲧衮磙绲丨" };
const char pinyin_mb_guo[] = { "过国果裹锅郭涡埚椁聒馘猓崞掴帼呙虢蜾蝈" };
const char pinyin_mb_ha[] = { "哈蛤虾铪呵" };
const char pinyin_mb_hai[] = { "还海害咳氦孩骇骸亥嗨醢胲" };
const char pinyin_mb_han[] = { "喊含汗寒汉旱酣韩焊涵函憨翰罕撼捍憾悍邯邗菡撖瀚阚顸蚶焓颔晗鼾厂旰" };
const char pinyin_mb_hang[] = { "行巷航夯杭吭颃沆绗珩桁炕肮" };
const char pinyin_mb_hao[] = { "好号浩嚎壕郝毫豪耗貉镐昊颢灏嚆蚝嗥皓蒿濠薅" };
const char pinyin_mb_he[] = { "和喝合河禾核何呵荷贺赫褐盒鹤菏貉阂涸吓嗬劾盍翮阖颌壑诃纥曷鹄" };
const char pinyin_mb_hei[] = { "黑嘿嗨" };
const char pinyin_mb_hen[] = { "很狠恨痕哏" };
const char pinyin_mb_heng[] = { "横恒哼衡亨行桁珩蘅" };
const char pinyin_mb_hong[] = { "红轰哄虹洪宏烘鸿弘讧訇蕻闳薨黉荭泓" };
const char pinyin_mb_hou[] = { "后厚吼喉侯候猴鲎篌堠後逅糇骺瘊" };
const char pinyin_mb_hu[] = { "湖户呼虎壶互胡护糊弧忽狐蝴葫沪乎戏核和瑚唬鹕冱怙鹱笏戽扈鹘浒祜醐琥囫烀轷瓠煳斛鹄猢惚岵滹觳唿槲" };
const char pinyin_mb_hua[] = { "话花化画华划滑哗猾豁铧桦骅砉" };
const char pinyin_mb_huai[] = { "坏怀淮槐徊划踝" };
const char pinyin_mb_huan[] = { "换还唤环患缓欢幻宦涣焕豢桓痪漶獾擐逭鲩郇鬟寰奂锾圜洹萑缳浣垸" };
const char pinyin_mb_huang[] = { "黄慌晃荒簧凰皇谎惶蝗磺恍煌幌隍肓潢篁徨鳇遑癀湟蟥璜" };
const char pinyin_mb_hui[] = { "回会灰绘挥汇辉毁悔惠晦徽恢秽慧贿蛔讳徊卉烩诲彗浍珲蕙喙恚哕晖隳麾诙蟪茴洄咴虺荟缋堕桧" };
const char pinyin_mb_hun[] = { "混昏荤浑婚魂阍珲馄溷诨" };
const char pinyin_mb_huo[] = { "或活火伙货和获祸豁霍惑嚯镬耠劐藿攉锪蠖钬夥" };
const char pinyin_mb_ji[] = { "几及急既即机鸡积记级极计挤己季寄纪系基激吉脊际击圾畸箕肌饥迹讥姬绩棘辑籍缉集疾汲嫉蓟技冀伎祭剂悸济寂期其奇忌齐妓继给革稽墼洎鲚屐齑戟鲫嵇矶稷戢虮诘笈暨笄剞叽蒺跻嵴掎跽霁唧畿荠瘠玑羁丌偈芨佶赍楫髻咭蕺觊麂" };
const char pinyin_mb_jia[] = { "家加假价架甲佳夹嘉驾嫁枷荚颊钾稼茄贾铗葭迦戛浃镓痂恝岬跏嘏伽胛笳珈瘕郏袈蛱拮挟袷颉" };
const char pinyin_mb_jian[] = { "见件减尖间键贱肩兼建检箭煎简剪歼监坚奸健艰荐剑渐溅涧鉴浅践捡柬笺俭碱硷拣舰槛缄茧饯翦鞯戋谏牮枧腱趼缣搛戬毽菅鲣笕谫楗囝蹇裥踺睑謇鹣蒹僭锏湔堑犍" };
const char pinyin_mb_jiang[] = { "将讲江奖降浆僵姜酱蒋疆匠强桨虹豇礓缰犟耩绛茳糨洚" };
const char pinyin_mb_jiao[] = { "叫脚交角教较缴觉焦胶娇绞校搅骄狡浇矫郊嚼蕉轿窖椒礁饺铰酵侥剿徼艽僬蛟敫峤跤姣皎茭鹪噍醮佼湫鲛挢" };
const char pinyin_mb_jie[] = { "接节街借皆截解界结届姐揭戒介阶劫芥竭洁疥藉价楷秸桔杰捷诫睫家偈桀喈拮骱羯蚧嗟颉鲒婕碣讦孑疖诘卩" };
const char pinyin_mb_jin[] = { "进近今仅紧金斤尽劲禁浸锦晋筋津谨巾襟烬靳廑瑾馑槿衿堇荩矜噤缙卺妗赆觐" };
const char pinyin_mb_jing[] = { "竟静井惊经镜京净敬精景警竞境径荆晶鲸粳颈兢茎睛劲痉靖肼獍阱腈弪刭憬婧胫菁儆旌迳靓泾箐" };
const char pinyin_mb_jiong[] = { "窘炯扃迥炅冂" };
const char pinyin_mb_jiu[] = { "就九酒旧久揪救纠舅究韭厩臼玖灸咎疚赳鹫蹴僦柩桕鬏鸠阄啾" };
const char pinyin_mb_ju[] = { "句举巨局具距锯剧居聚拘菊矩沮拒惧鞠狙驹且据柜桔俱车咀疽踞炬倨醵裾屦犋苴窭飓锔椐苣琚掬榘龃趄莒雎遽橘踽榉鞫钜讵枸渠瞿" };
const char pinyin_mb_juan[] = { "卷圈倦鹃捐娟眷绢鄄锩蠲镌狷桊涓隽" };
const char pinyin_mb_jue[] = { "决绝觉角爵掘诀撅倔抉攫嚼脚桷噱橛嗟觖劂爝矍镢獗珏崛蕨噘谲蹶孓厥" };
const char pinyin_mb_jun[] = { "军君均菌俊峻龟竣骏钧浚郡筠麇皲捃匀" };
const char pinyin_mb_ka[] = { "卡喀咯咖胩咔佧" };
const char pinyin_mb_kai[] = { "开揩凯慨楷垲剀锎铠锴忾恺蒈劾" };
const char pinyin_mb_kan[] = { "看砍堪刊嵌坎槛勘龛戡侃瞰莰阚凵" };
const char pinyin_mb_kang[] = { "抗炕扛糠康慷亢钪闶伉" };
const char pinyin_mb_kao[] = { "靠考烤拷栲犒尻铐" };
const char pinyin_mb_ke[] = { "咳可克棵科颗刻课客壳渴苛柯磕坷呵恪岢蝌缂蚵轲窠钶氪颏瞌锞稞珂髁疴嗑溘骒铪" };
const char pinyin_mb_ken[] = { "肯啃恳垦裉龈" };
const char pinyin_mb_keng[] = { "坑吭铿" };
const char pinyin_mb_kong[] = { "空孔控恐倥崆箜" };
const char pinyin_mb_kou[] = { "口扣抠寇蔻芤眍筘叩佝" };
const char pinyin_mb_ku[] = { "哭库苦枯裤窟酷刳骷喾堀绔" };
const char pinyin_mb_kua[] = { "跨垮挎夸胯侉" };
const char pinyin_mb_kuai[] = { "快块筷会侩哙蒯浍郐狯脍" };
const char pinyin_mb_kuan[] = { "宽款髋" };
const char pinyin_mb_kuang[] = { "矿筐狂框况旷匡眶诳邝纩夼诓圹贶哐磺湟" };
const char pinyin_mb_kui[] = { "亏愧奎窥溃葵魁馈盔傀岿匮愦揆睽跬聩篑喹逵暌蒉悝喟馗蝰隗夔" };
const char pinyin_mb_kun[] = { "捆困昆坤鲲锟髡琨醌阃悃" };
const char pinyin_mb_kuo[] = { "阔扩括廓适蛞栝" };
const char pinyin_mb_la[] = { "拉啦辣蜡腊喇垃蓝落瘌邋砬剌旯" };
const char pinyin_mb_lai[] = { "来赖莱濑赉崃涞铼籁徕睐癞" };
const char pinyin_mb_lan[] = { "蓝兰烂拦篮懒栏揽缆滥阑谰婪澜览榄岚褴镧斓罱漤啉" };
const char pinyin_mb_lang[] = { "浪狼廊郎朗榔琅稂螂莨啷锒阆蒗" };
const char pinyin_mb_lao[] = { "老捞牢劳烙涝落姥酪络佬潦耢铹醪铑唠栳崂痨" };
const char pinyin_mb_le[] = { "了乐勒肋鳓仂叻泐嘞" };
const char pinyin_mb_lei[] = { "类累泪雷垒勒擂蕾肋镭儡磊缧诔耒酹羸嫘檑嘞漯" };
const char pinyin_mb_leng[] = { "冷棱楞愣塄" };
const char pinyin_mb_li[] = { "里离力立李例哩理利梨厘礼历丽吏砾漓莉傈荔俐痢狸粒沥隶栗璃鲤厉励犁黎篱郦鹂笠坜苈鳢缡跞蜊锂悝澧粝蓠枥蠡鬲呖砺嫠篥疠疬猁藜溧鲡戾栎唳醴轹詈骊罹逦俪喱雳黧莅俚蛎娌" };
const char pinyin_mb_lia[] = { "俩" };
const char pinyin_mb_lian[] = { "连联练莲恋脸炼链敛怜廉帘镰涟蠊琏殓蔹鲢奁潋臁裢濂裣楝" };
const char pinyin_mb_liang[] = { "两亮辆凉粮梁量良晾谅俩粱墚靓踉椋魉莨" };
const char pinyin_mb_liao[] = { "了料撩聊撂疗廖燎辽僚寥镣潦钌蓼尥寮缭獠鹩嘹" };
const char pinyin_mb_lie[] = { "列裂猎劣烈咧埒捩鬣趔躐冽洌" };
const char pinyin_mb_lin[] = { "林临淋邻磷鳞赁吝拎琳霖凛遴嶙蔺粼麟躏辚廪懔瞵檩膦啉" };
const char pinyin_mb_ling[] = { "另令领零铃玲灵岭龄凌陵菱伶羚棱翎蛉苓绫瓴酃呤泠棂柃鲮聆囹" };
const char pinyin_mb_liu[] = { "六流留刘柳溜硫瘤榴琉馏碌陆绺锍鎏镏浏骝旒鹨熘遛" };
const char pinyin_mb_lo[] = { "咯" };
const char pinyin_mb_long[] = { "龙拢笼聋隆垄弄咙窿陇垅胧珑茏泷栊癃砻" };
const char pinyin_mb_lou[] = { "楼搂漏陋露娄篓偻蝼镂蒌耧髅喽瘘嵝" };
const char pinyin_mb_lu[] = { "路露录鹿陆炉卢鲁卤芦颅庐碌掳绿虏赂戮潞禄麓六鲈栌渌蓼逯泸轳氇簏橹辂垆胪噜镥辘漉撸璐鸬鹭舻" };
const char pinyin_mb_luan[] = { "乱卵滦峦孪挛栾銮脔娈鸾" };
const char pinyin_mb_lun[] = { "论轮抡伦沦仑纶囵" };
const char pinyin_mb_luo[] = { "落罗锣裸骡烙箩螺萝洛骆逻络咯荦漯蠃雒倮硌椤捋脶瘰摞泺珞镙猡跞" };
const char pinyin_mb_lv[] = { "绿率铝驴旅屡滤吕律氯缕侣虑履偻膂榈闾捋褛稆" };
const char pinyin_mb_lue[] = { "略掠锊" };
const char pinyin_mb_ma[] = { "吗妈马嘛麻骂抹码玛蚂摩唛蟆犸嬷杩" };
const char pinyin_mb_mai[] = { "买卖迈埋麦脉劢霾荬" };
const char pinyin_mb_man[] = { "满慢瞒漫蛮蔓曼馒埋谩幔鳗墁螨镘颟鞔缦熳" };
const char pinyin_mb_mang[] = { "忙芒盲莽茫氓硭邙蟒漭" };
const char pinyin_mb_mao[] = { "毛冒帽猫矛卯貌茂贸铆锚茅耄茆瑁蝥髦懋昴牦瞀峁袤蟊旄泖" };
const char pinyin_mb_me[] = { "么麽" };
const char pinyin_mb_mei[] = { "没每煤镁美酶妹枚霉玫眉梅寐昧媒糜媚谜沫嵋猸袂湄浼鹛莓魅镅楣" };
const char pinyin_mb_men[] = { "门们闷懑扪钔焖汶鞔" };
const char pinyin_mb_meng[] = { "猛梦蒙锰孟盟檬萌氓礞蜢勐懵甍蠓虻朦艋艨瞢" };
const char pinyin_mb_mi[] = { "米密迷眯蜜谜觅秘弥幂靡糜泌醚蘼縻咪汨麋祢猕弭谧芈脒宓敉嘧糸" };
const char pinyin_mb_mian[] = { "面棉免绵眠缅勉冕娩腼湎眄沔黾渑宀" };
const char pinyin_mb_miao[] = { "秒苗庙妙描瞄藐渺眇缪缈邈淼喵杪鹋" };
const char pinyin_mb_mie[] = { "灭蔑咩篾蠛乜" };
const char pinyin_mb_min[] = { "民抿敏闽皿悯珉愍缗闵玟苠泯黾鳘岷" };
const char pinyin_mb_ming[] = { "名明命鸣铭螟盟冥瞑暝茗溟酩" };
const char pinyin_mb_miu[] = { "谬缪" };
const char pinyin_mb_mo[] = { "摸磨抹末膜墨没莫默魔模摩摹漠陌蘑脉沫万无冒寞秣瘼殁镆嫫谟蓦貊貘麽茉馍耱么嘿嬷" };
const char pinyin_mb_mou[] = { "某谋牟眸蛑鍪侔缪哞厶" };
const char pinyin_mb_mu[] = { "木母亩幕目墓牧牟模穆暮牡拇募慕睦姆姥钼毪坶沐仫苜" };
const char pinyin_mb_na[] = { "那拿哪纳钠娜呐南衲捺镎肭内" };
const char pinyin_mb_nai[] = { "乃耐奶奈氖哪萘艿柰鼐佴能" };
const char pinyin_mb_nan[] = { "难南男赧囡蝻楠喃腩囝" };
const char pinyin_mb_nang[] = { "囊馕曩囔攮" };
const char pinyin_mb_nao[] = { "闹脑恼挠淖孬铙瑙垴呶蛲猱硇" };
const char pinyin_mb_ne[] = { "呢哪那呐讷疒" };
const char pinyin_mb_nei[] = { "内哪馁那" };
const char pinyin_mb_nen[] = { "嫩恁" };
const char pinyin_mb_neng[] = { "能" };
const char pinyin_mb_ng[] = { "嗯" };
const char pinyin_mb_ni[] = { "你泥拟腻逆呢溺倪尼匿妮霓铌昵坭祢猊伲怩鲵睨旎" };
const char pinyin_mb_nian[] = { "年念捻撵拈碾蔫粘廿黏辇鲇鲶埝辗" };
const char pinyin_mb_niang[] = { "娘酿" };
const char pinyin_mb_niao[] = { "鸟尿袅茑脲嬲溺" };
const char pinyin_mb_nie[] = { "捏镍聂孽涅镊啮陧蘖嗫臬蹑颞乜" };
const char pinyin_mb_nin[] = { "您恁" };
const char pinyin_mb_ning[] = { "拧凝宁柠狞泞佞甯咛聍" };
const char pinyin_mb_niu[] = { "牛扭纽钮狃忸妞拗" };
const char pinyin_mb_nong[] = { "弄浓农脓哝侬" };
const char pinyin_mb_nou[] = { "耨" };
const char pinyin_mb_nu[] = { "怒努奴孥胬驽弩呶帑" };
const char pinyin_mb_nv[] = { "女钕恧衄" };
const char pinyin_mb_nue[] = { "虐疟谑" };
const char pinyin_mb_nuan[] = { "暖" };
const char pinyin_mb_nuo[] = { "挪诺懦糯娜喏傩锘搦" };
const char pinyin_mb_o[] = { "哦喔噢" };
const char pinyin_mb_ou[] = { "偶呕欧藕鸥区沤殴怄瓯讴耦" };
const char pinyin_mb_pa[] = { "怕爬趴啪耙扒帕琶派筢杷葩钯" };
const char pinyin_mb_pai[] = { "派排拍牌迫徘湃哌俳蒎" };
const char pinyin_mb_pan[] = { "盘盼判攀畔潘叛磐番般胖襻蟠袢泮拚爿蹒" };
const char pinyin_mb_pang[] = { "旁胖耪庞乓膀磅滂彷逄螃仿" };
const char pinyin_mb_pao[] = { "跑抛炮泡刨袍咆狍匏庖疱脬" };
const char pinyin_mb_pei[] = { "陪配赔呸胚佩培沛裴旆锫帔醅霈辔淠" };
const char pinyin_mb_pen[] = { "喷盆湓" };
const char pinyin_mb_peng[] = { "碰捧棚砰蓬朋彭鹏烹硼膨抨澎篷怦堋蟛嘭" };
const char pinyin_mb_pi[] = { "批皮披匹劈辟坯屁脾僻疲痞霹琵毗啤譬砒否貔丕圮媲癖仳擗郫甓枇睥蜱鼙邳吡陂铍庀罴埤纰陴淠噼蚍裨芘" };
const char pinyin_mb_pian[] = { "片篇骗偏便扁翩缏犏骈胼蹁谝" };
const char pinyin_mb_piao[] = { "票飘漂瓢朴螵莩嫖瞟殍缥嘌骠剽" };
const char pinyin_mb_pie[] = { "瞥撇苤氕" };
const char pinyin_mb_pin[] = { "品贫聘拼频嫔榀姘牝颦" };
const char pinyin_mb_ping[] = { "平凭瓶评屏乒萍苹坪冯娉鲆枰俜" };
const char pinyin_mb_po[] = { "破坡颇婆泼迫泊魄朴繁粕笸皤钋陂鄱攴叵珀钷泺" };
const char pinyin_mb_pou[] = { "剖掊裒" };
const char pinyin_mb_pu[] = { "扑铺谱脯仆蒲葡朴菩莆瀑曝埔圃浦堡普暴镨噗匍溥濮氆蹼璞镤攴攵" };
const char pinyin_mb_qi[] = { "起其七气期齐器妻骑汽棋奇欺漆启戚柒岂砌弃泣祁凄企乞契歧祈栖畦脐崎稽迄缉沏讫旗祺颀骐屺岐蹊萁蕲桤憩芪荠萋芑汔亟鳍俟槭嘁蛴綦亓欹琪麒琦蜞圻杞葺碛淇祗耆绮丌伎綮" };
const char pinyin_mb_qia[] = { "恰卡掐洽袷葜髂" };
const char pinyin_mb_qian[] = { "前钱千牵浅签欠铅嵌钎迁钳乾谴谦潜歉纤扦遣黔堑仟岍钤褰箝掮搴倩慊悭愆虔芡荨缱佥芊阡肷茜椠犍骞凵" };
const char pinyin_mb_qiang[] = { "强枪墙抢腔呛羌蔷将蜣跄戗襁戕炝镪锖锵羟樯嫱" };
const char pinyin_mb_qiao[] = { "桥瞧敲巧翘锹壳鞘撬悄俏窍雀乔侨峭橇樵荞跷硗憔谯鞒愀缲诮劁峤" };
const char pinyin_mb_qie[] = { "切且怯窃茄砌郄趄惬锲妾箧慊伽挈" };
const char pinyin_mb_qin[] = { "亲琴侵勤擒寝秦芹沁禽钦吣覃矜衾芩溱廑嗪螓噙揿檎锓" };
const char pinyin_mb_qing[] = { "请轻清青情晴氢倾庆擎顷亲卿氰圊謦檠箐苘蜻黥罄鲭磬綮倩" };
const char pinyin_mb_qiong[] = { "穷琼跫穹邛蛩茕銎筇" };
const char pinyin_mb_qiu[] = { "求球秋丘泅仇邱囚酋龟楸蚯裘糗蝤巯逑俅虬赇鳅犰湫鼽遒艽" };
const char pinyin_mb_qu[] = { "去取区娶渠曲趋趣屈驱蛆躯龋戌蠼蘧祛蕖磲劬诎鸲阒麴癯衢黢璩氍觑蛐朐瞿岖苣" };
const char pinyin_mb_quan[] = { "全权劝圈拳犬泉券颧痊醛铨筌绻诠辁畎鬈悛蜷荃犭" };
const char pinyin_mb_que[] = { "却缺确雀瘸鹊炔榷阙阕悫芍" };
const char pinyin_mb_qui[] = { "鼽" };
const char pinyin_mb_qun[] = { "群裙逡麇" };
const char pinyin_mb_ran[] = { "染燃然冉髯苒蚺" };
const char pinyin_mb_rang[] = { "让嚷瓤攘壤穰禳" };
const char pinyin_mb_rao[] = { "饶绕扰荛桡娆" };
const char pinyin_mb_re[] = { "热若惹喏" };
const char pinyin_mb_ren[] = { "人任忍认刃仁韧妊纫壬饪轫仞荏葚衽稔亻" };
const char pinyin_mb_reng[] = { "仍扔艿" };
const char pinyin_mb_ri[] = { "日" };
const char pinyin_mb_rong[] = { "容绒融溶熔荣戎蓉冗茸榕狨嵘肜蝾" };
const char pinyin_mb_rou[] = { "肉揉柔糅蹂鞣" };
const char pinyin_mb_ru[] = { "如入汝儒茹乳褥辱蠕孺蓐襦铷嚅缛濡薷颥溽洳" };
const char pinyin_mb_ruan[] = { "软阮朊" };
const char pinyin_mb_rui[] = { "瑞蕊锐睿芮蚋枘蕤" };
const char pinyin_mb_run[] = { "闰润" };
const char pinyin_mb_ruo[] = { "若弱偌箬" };
const char pinyin_mb_sa[] = { "撒洒萨挲仨卅飒脎" };
const char pinyin_mb_sai[] = { "塞腮鳃思赛噻" };
const char pinyin_mb_san[] = { "三散伞叁馓糁毵霰参" };
const char pinyin_mb_sang[] = { "桑丧嗓颡磉搡" };
const char pinyin_mb_sao[] = { "扫嫂搔骚梢埽鳋臊缫瘙缲" };
const char pinyin_mb_se[] = { "色涩瑟塞啬铯穑槭" };
const char pinyin_mb_sen[] = { "森" };
const char pinyin_mb_seng[] = { "僧" };
const char pinyin_mb_sha[] = { "杀沙啥纱傻砂刹莎厦煞杉嗄唼鲨霎铩痧裟挲歃噎" };
const char pinyin_mb_shai[] = { "晒筛色酾" };
const char pinyin_mb_shan[] = { "山闪衫善扇杉删煽单珊掺赡栅苫掸膳陕汕擅缮嬗蟮芟禅跚鄯潸鳝姗剡骟疝膻讪钐舢埏彡" };
const char pinyin_mb_shang[] = { "上伤尚商赏晌墒汤裳熵觞绱殇垧" };
const char pinyin_mb_shao[] = { "少烧捎哨勺梢稍邵韶绍芍召鞘苕劭潲艄蛸筲杓" };
const char pinyin_mb_she[] = { "社射蛇设舌摄舍折涉赊赦慑奢歙厍畲猞麝滠佘拾揲" };
const char pinyin_mb_shei[] = { "谁" };
const char pinyin_mb_shen[] = { "身伸深婶神甚渗肾审申沈绅呻参砷什娠慎葚糁莘诜谂矧椹渖蜃哂胂吲" };
const char pinyin_mb_sheng[] = { "声省剩生升绳胜盛圣甥牲乘晟渑眚笙嵊" };
const char pinyin_mb_shi[] = { "是使十时事室市石师试史式识虱矢拾屎驶始似嘘示士世柿匙拭誓逝势什殖峙嗜噬失适仕侍释饰氏狮食恃蚀视实施湿诗尸豕莳埘铈舐鲥鲺贳轼蓍筮炻谥弑酾螫礻耆饣" };
const char pinyin_mb_shou[] = { "手受收首守瘦授兽售熟寿艏狩绶扌" };
const char pinyin_mb_shu[] = { "书树数熟输梳叔属束术述蜀黍鼠淑赎孰蔬疏戍竖墅庶薯漱恕枢暑殊抒曙署舒姝摅秫纾沭毹腧塾菽殳澍倏疋荼" };
const char pinyin_mb_shua[] = { "刷耍唰" };
const char pinyin_mb_shuai[] = { "摔甩率帅衰蟀" };
const char pinyin_mb_shuan[] = { "栓拴闩涮" };
const char pinyin_mb_shuang[] = { "双霜爽泷孀" };
const char pinyin_mb_shui[] = { "水谁睡税说氵" };
const char pinyin_mb_shun[] = { "顺吮瞬舜" };
const char pinyin_mb_shuo[] = { "说数硕烁朔搠妁槊蒴铄" };
const char pinyin_mb_si[] = { "四司丝撕似私嘶思寺斯食伺死厕肆饲嗣巳耜驷兕蛳厮汜锶泗笥咝鸶姒厶缌祀澌俟糸纟" };
const char pinyin_mb_song[] = { "送松耸宋颂诵怂讼竦菘淞悚嵩凇崧忪" };
const char pinyin_mb_sou[] = { "艘搜擞嗽嗾嗖飕叟薮锼馊瞍溲螋" };
const char pinyin_mb_su[] = { "素速诉塑宿俗苏肃粟酥缩溯僳愫簌觫稣夙嗉谡蔌涑" };
const char pinyin_mb_suan[] = { "酸算蒜狻" };
const char pinyin_mb_sui[] = { "岁随碎虽穗遂尿隋髓绥隧祟眭谇濉邃燧荽睢粹" };
const char pinyin_mb_sun[] = { "孙损笋榫荪飧狲隼" };
const char pinyin_mb_suo[] = { "所缩锁琐索梭蓑莎唆挲睃嗍唢桫嗦娑羧" };
const char pinyin_mb_ta[] = { "他她它踏塔塌拓獭挞蹋溻趿鳎沓榻漯遢铊闼嗒" };
const char pinyin_mb_tai[] = { "太抬台态胎苔泰酞汰炱肽跆呔鲐钛薹邰骀" };
const char pinyin_mb_tan[] = { "谈叹探滩弹碳摊潭贪坛痰毯坦炭瘫谭坍檀袒钽郯镡锬覃澹昙忐" };
const char pinyin_mb_tang[] = { "躺趟堂糖汤塘烫倘淌唐搪棠膛螳樘羰醣瑭镗傥饧溏耥帑铴螗" };
const char pinyin_mb_tao[] = { "套掏逃桃讨淘涛滔陶绦萄鼗啕洮韬饕叨焘" };
const char pinyin_mb_te[] = { "特忑慝铽忒" };
const char pinyin_mb_teng[] = { "疼腾藤誊滕" };
const char pinyin_mb_ti[] = { "提替体题踢蹄剃剔梯锑啼涕嚏惕屉醍鹈绨缇倜裼逖荑悌棣" };
const char pinyin_mb_tian[] = { "天田添填甜舔恬腆佃掭钿阗忝殄畋栝" };
const char pinyin_mb_tiao[] = { "条跳挑调迢眺龆笤祧蜩髫佻窕鲦苕粜啁" };
const char pinyin_mb_tie[] = { "铁贴帖萜餮" };
const char pinyin_mb_ting[] = { "听停挺厅亭艇庭廷烃汀町莛铤葶婷蜓梃霆" };
const char pinyin_mb_tong[] = { "同通痛铜桶筒捅统童彤桐瞳恫侗酮潼茼仝砼峒恸佟嗵垌僮" };
const char pinyin_mb_tou[] = { "头偷透投钭骰亠愉" };
const char pinyin_mb_tu[] = { "土图兔涂吐秃突徒凸途屠酴荼钍菟堍" };
const char pinyin_mb_tuan[] = { "团湍疃抟彖" };
const char pinyin_mb_tui[] = { "腿推退褪颓蜕煺忒弟" };
const char pinyin_mb_tun[] = { "吞屯褪臀囤氽饨豚暾" };
const char pinyin_mb_tuo[] = { "拖脱托妥驮拓驼椭唾鸵陀魄橐柝跎乇坨佗庹酡柁鼍沱箨砣铊隋舵" };
const char pinyin_mb_wa[] = { "挖瓦蛙哇娃洼凹袜佤娲腽" };
const char pinyin_mb_wai[] = { "外歪崴呙" };
const char pinyin_mb_wan[] = { "完万晚碗玩弯挽湾丸腕宛婉烷顽豌惋娩皖蔓莞脘蜿绾芄琬纨剜畹菀箢" };
const char pinyin_mb_wang[] = { "望忘王往网亡枉旺汪妄芒辋魍惘罔尢" };
const char pinyin_mb_wei[] = { "为位未围喂胃微味尾伪威伟卫危违委魏唯维畏惟韦巍蔚谓尉潍纬慰桅萎苇渭遗葳帏艉鲔娓逶闱隈沩玮涠帷崴隗诿洧偎猥猬嵬軎韪炜煨圩薇痿倭隹" };
const char pinyin_mb_wen[] = { "问文闻稳温吻蚊纹瘟紊汶阌刎雯璺韫" };
const char pinyin_mb_weng[] = { "翁嗡瓮蕹蓊" };
const char pinyin_mb_wo[] = { "我握窝卧挝沃蜗涡斡倭幄龌肟莴喔渥硪媪" };
const char pinyin_mb_wu[] = { "无五屋物舞雾误捂污悟勿钨武戊务呜伍吴午吾侮乌毋恶诬芜巫晤梧坞妩蜈牾寤兀怃阢邬忤骛於鋈仵杌鹜婺迕痦芴焐庑鹉鼯浯圬亡唔" };
const char pinyin_mb_xi[] = { "西洗细吸戏系喜席稀溪熄锡膝息袭惜习嘻夕悉矽熙希檄牺晰昔媳硒铣烯腊析隙栖汐犀蜥奚浠葸饩屣玺嬉禊兮翕穸禧僖淅蓰舾蹊醯欷皙蟋羲茜徙隰唏曦螅歙樨阋粞熹觋菥鼷裼舄郄褶鳃郗" };
const char pinyin_mb_xia[] = { "下吓夏峡虾瞎霞狭匣侠辖厦暇唬狎柙呷黠硖罅遐瑕假" };
const char pinyin_mb_xian[] = { "先线县现显掀闲献嫌陷险鲜弦衔馅限咸锨仙腺贤纤宪舷涎羡铣见苋藓岘痫莶籼娴蚬猃祆冼燹跣跹酰暹氙鹇筅霰彡" };
const char pinyin_mb_xiang[] = { "想向象项响香乡相像箱巷享镶厢降翔祥橡详湘襄飨鲞骧蟓庠芗饷缃葙" };
const char pinyin_mb_xiao[] = { "小笑消削销萧效宵晓肖孝硝淆啸霄哮嚣校魈蛸骁枵哓崤筱潇逍枭绡箫俏姣" };
const char pinyin_mb_xie[] = { "写些鞋歇斜血谢卸挟屑蟹泻懈泄楔邪协械谐蝎携胁解契叶绁颉缬獬榭廨撷偕瀣渫亵榍邂薤躞燮勰鲑" };
const char pinyin_mb_xin[] = { "新心欣信芯薪锌辛寻衅忻歆囟莘镡馨鑫昕忄" };
const char pinyin_mb_xing[] = { "性行型形星醒姓腥刑杏兴幸邢猩惺省硎悻荥陉擤荇饧" };
const char pinyin_mb_xiong[] = { "胸雄凶兄熊汹匈芎" };
const char pinyin_mb_xiu[] = { "修锈绣休羞宿嗅袖秀朽臭溴貅馐髹鸺咻庥岫" };
const char pinyin_mb_xu[] = { "许须需虚嘘蓄续序叙畜絮婿戌徐旭绪吁酗恤墟糈勖栩浒蓿顼圩洫胥醑诩溆煦盱砉" };
const char pinyin_mb_xuan[] = { "选悬旋玄宣喧轩绚眩癣券暄楦儇渲漩泫铉璇煊碹镟炫揎萱痃谖" };
const char pinyin_mb_xue[] = { "学雪血靴穴削薛踅噱鳕泶谑彐" };
const char pinyin_mb_xun[] = { "寻讯熏训循殉旬巡迅驯汛逊勋荤询浚巽鲟浔埙恂獯醺洵郇峋蕈薰荀窨曛徇孙荨" };
const char pinyin_mb_ya[] = { "呀压牙押芽鸭轧哑亚涯丫雅衙鸦讶蚜垭疋砑琊桠睚娅痖岈氩伢迓揠崖厌吖" };
const char pinyin_mb_yan[] = { "眼烟沿盐言演严咽淹炎掩厌宴岩研延堰验艳殷阉砚雁唁彦焰蜒衍谚燕颜阎铅焉奄芫厣阏菸魇琰滟焱赝筵腌兖剡餍恹罨檐湮偃谳胭晏闫俨郾酽鄢妍鼹崦阽嫣埏讠" };
const char pinyin_mb_yang[] = { "样养羊洋仰扬秧氧痒杨漾阳殃央鸯佯疡炀恙徉鞅泱蛘烊怏" };
const char pinyin_mb_yao[] = { "要摇药咬腰窑舀邀妖谣遥姚瑶耀尧钥侥陶约疟珧夭鳐鹞轺爻吆铫幺崾肴曜徭杳窈么繇" };
const char pinyin_mb_ye[] = { "也夜业野叶爷页液掖腋冶噎耶咽曳椰邪谒邺晔烨揶铘靥揲" };
const char pinyin_mb_yi[] = { "一以已亿衣移依易医乙仪亦椅益倚姨翼译伊蛇遗食艾胰疑沂宜异彝壹蚁谊揖铱矣翌艺抑绎邑蛾屹尾役臆逸肄疫颐裔意毅忆义夷溢诣议怿痍镒癔怡驿旖熠酏翊欹峄圯殪嗌咦懿噫劓诒饴漪佚咿瘗猗眙羿弈苡荑仡佾贻钇缢迤刈悒黟翳弋奕蜴埸挹嶷薏呓轶镱舣衤" };
const char pinyin_mb_yin[] = { "因引印银音饮阴隐荫吟尹寅茵淫殷姻烟堙鄞喑夤胤龈吲圻狺垠霪蚓氤铟窨瘾洇茚廴湮" };
const char pinyin_mb_ying[] = { "应硬影营迎映蝇赢鹰英颖莹盈婴樱缨荧萤萦楹蓥瘿茔鹦媵莺璎郢嘤撄瑛滢潆嬴罂瀛膺荥颍景" };
const char pinyin_mb_yo[] = { "哟育唷" };
const char pinyin_mb_yong[] = { "用涌永拥蛹勇雍咏泳佣踊痈庸臃恿壅慵俑墉鳙邕喁甬饔镛" };
const char pinyin_mb_you[] = { "有又由右油游幼优友铀忧尤犹诱悠邮酉佑釉幽疣攸蚰莠鱿卣黝莸猷蚴宥牖囿柚蝣莜鼬铕蝤繇呦侑尢" };
const char pinyin_mb_yu[] = { "与于欲鱼雨余遇语愈狱玉渔予誉育愚羽虞娱淤舆屿禹宇迂俞逾域芋郁谷吁盂喻峪御愉粥渝尉榆隅浴寓裕预豫驭蔚妪嵛雩馀阈窬鹆妤揄窳觎臾舁龉蓣煜钰谀纡於竽瑜禺聿欤俣伛圄鹬庾昱萸瘐谕鬻圉瘀熨饫毓燠腴狳菀蜮蝓吾喁菸肀" };
const char pinyin_mb_yuan[] = { "远员元院圆原愿园援猿怨冤源缘袁渊苑垣鸳辕圜鼋橼媛爰眢鸢掾芫沅瑗螈箢塬垸" };
const char pinyin_mb_yue[] = { "月越约跃阅乐岳悦曰说粤钥瀹钺刖龠栎樾哕" };
const char pinyin_mb_yun[] = { "云运晕允匀韵陨孕耘蕴酝郧员氲恽愠郓芸筠韫昀狁殒纭熨媪菀" };
const char pinyin_mb_za[] = { "杂砸咋匝扎咱咂拶" };
const char pinyin_mb_zai[] = { "在再灾载栽宰哉崽甾仔" };
const char pinyin_mb_zan[] = { "咱暂攒赞簪趱糌瓒拶昝錾" };
const char pinyin_mb_zang[] = { "脏葬赃藏臧驵奘" };
const char pinyin_mb_zao[] = { "早造遭糟灶燥枣凿躁藻皂噪澡蚤唣" };
const char pinyin_mb_ze[] = { "则责择泽咋侧箦舴帻迮啧仄昃笮赜" };
const char pinyin_mb_zei[] = { "贼" };
const char pinyin_mb_zen[] = { "怎谮" };
const char pinyin_mb_zeng[] = { "增赠憎曾综缯罾甑锃" };
const char pinyin_mb_zha[] = { "扎炸渣闸眨榨乍轧诈喳札铡揸吒咤哳猹砟痄蚱齄查蜡栅咋喋楂柞" };
const char pinyin_mb_zhai[] = { "摘窄债斋寨择翟宅侧祭砦瘵" };
const char pinyin_mb_zhan[] = { "站占战盏沾粘毡展栈詹颤蘸湛绽斩辗崭瞻谵搌旃" };
const char pinyin_mb_zhang[] = { "张章长帐仗丈掌涨账樟杖彰漳胀瘴障仉嫜幛鄣璋嶂獐蟑" };
const char pinyin_mb_zhao[] = { "找着照招罩爪兆朝昭沼肇嘲召赵棹啁钊笊诏濯" };
const char pinyin_mb_zhe[] = { "着这者折遮蛰哲蔗锗辙浙柘辄赭摺鹧磔褶蜇谪乇" };
const char pinyin_mb_zhen[] = { "真阵镇针震枕振斟珍疹诊甄砧臻贞侦缜蓁祯箴轸榛稹赈朕鸩胗浈桢畛圳椹溱" };
const char pinyin_mb_zheng[] = { "正整睁争挣征怔证症郑拯丁蒸狰政峥钲铮筝诤徵鲭帧" };
const char pinyin_mb_zhi[] = { "只之直知制指纸支芝枝稚吱蜘质肢脂汁炙织职痔植抵殖执值侄址滞止趾治旨窒志挚掷至致置帜识峙氏智秩帙摭黹桎枳轵忮祉蛭膣觯郅栀彘芷祗咫鸷絷踬胝骘轾痣陟踯雉埴贽卮酯豸跖栉郦夂" };
const char pinyin_mb_zhong[] = { "中重种钟肿众终盅忠仲衷踵舯螽锺冢忪夂" };
const char pinyin_mb_zhou[] = { "周洲皱粥州轴舟昼骤宙诌肘帚咒繇胄纣荮啁碡绉籀妯酎" };
const char pinyin_mb_zhu[] = { "住主猪竹株煮筑贮铸嘱拄注祝驻属术珠瞩蛛朱柱诸诛逐助烛蛀潴洙伫瘃翥茱苎橥舳杼箸炷侏铢疰渚褚躅麈邾槠竺澍丶" };
const char pinyin_mb_zhua[] = { "抓爪挝" };
const char pinyin_mb_zhuai[] = { "拽转" };
const char pinyin_mb_zhuan[] = { "转专砖赚传撰篆颛馔啭沌" };
const char pinyin_mb_zhuang[] = { "装撞庄壮桩状幢妆僮奘戆" };
const char pinyin_mb_zhui[] = { "追坠缀锥赘椎骓惴缒隹揣" };
const char pinyin_mb_zhun[] = { "准谆屯肫窀淳" };
const char pinyin_mb_zhuo[] = { "捉桌着啄拙灼浊卓琢缴茁酌擢焯濯诼浞涿倬镯禚斫棹淖躅" };
const char pinyin_mb_zi[] = { "字自子紫籽资姿吱滓仔兹咨孜渍滋淄笫粢龇秭恣谘趑缁梓鲻锱孳耔觜髭赀茈訾嵫眦姊辎甾" };
const char pinyin_mb_zong[] = { "总纵宗棕综踪鬃偬粽枞腙" };
const char pinyin_mb_zou[] = { "走揍奏邹鲰鄹陬驺诹楱" };
const char pinyin_mb_zu[] = { "组族足阻租祖诅菹镞卒俎" };
const char pinyin_mb_zuan[] = { "钻纂赚攥缵躜" };
const char pinyin_mb_zui[] = { "最嘴醉罪堆咀觜蕞羧" };
const char pinyin_mb_zun[] = { "尊遵鳟撙樽奠" };
const char pinyin_mb_zuo[] = { "做作坐左座昨凿琢撮佐笮酢唑祚胙怍阼柞嘬" };

const char pinyin_mb_space[] = { "" };



/*"拼音输入法查询码表,二级字母索引表(index)"*/
py_index_t pinyin_index_a[] = { {"",pinyin_mb_a},
                                    {"i",pinyin_mb_ai},
                                    {"n",pinyin_mb_an},
                                    {"ng",pinyin_mb_ang},
                                    {"o",pinyin_mb_ao} };
py_index_t pinyin_index_b[] = { {"a",pinyin_mb_ba},
                                    {"ai",pinyin_mb_bai},
                                    {"an",pinyin_mb_ban},
                                    {"ang",pinyin_mb_bang},
                                    {"ao",pinyin_mb_bao},
                                    {"ei",pinyin_mb_bei},
                                    {"en",pinyin_mb_ben},
                                    {"eng",pinyin_mb_beng},
                                    {"i",pinyin_mb_bi},
                                    {"ian",pinyin_mb_bian},
                                    {"iao",pinyin_mb_biao},
                                    {"ie",pinyin_mb_bie},
                                    {"in",pinyin_mb_bin},
                                    {"ing",pinyin_mb_bing},
                                    {"o",pinyin_mb_bo},
                                    {"u",pinyin_mb_bu} };
py_index_t pinyin_index_c[] = { {"a",pinyin_mb_ca},
                                    {"ai",pinyin_mb_cai},
                                    {"an",pinyin_mb_can},
                                    {"ang",pinyin_mb_cang},
                                    {"ao",pinyin_mb_cao},
                                    {"e",pinyin_mb_ce},
                                    {"en",pinyin_mb_cen},
                                    {"eng",pinyin_mb_ceng},
                                    {"ha",pinyin_mb_cha},
                                    {"h",pinyin_mb_cha},
                                    {"hai",pinyin_mb_chai},
                                    {"han",pinyin_mb_chan},
                                    {"hang",pinyin_mb_chang},
                                    {"hao",pinyin_mb_chao},
                                    {"he",pinyin_mb_che},
                                    {"hen",pinyin_mb_chen},
                                    {"heng",pinyin_mb_cheng},
                                    {"hi",pinyin_mb_chi},
                                    {"hong",pinyin_mb_chong},
                                    {"hou",pinyin_mb_chou},
                                    {"hu",pinyin_mb_chu},
                                    {"huai",pinyin_mb_chuai},
                                    {"huan",pinyin_mb_chuan},
                                    {"huang",pinyin_mb_chuang},
                                    {"hui",pinyin_mb_chui},
                                    {"hun",pinyin_mb_chun},
                                    {"huo",pinyin_mb_chuo},
                                    {"i",pinyin_mb_ci},
                                    {"o",pinyin_mb_cong},
                                    {"ong",pinyin_mb_cong},
                                    {"ou",pinyin_mb_cou},
                                    {"u",pinyin_mb_cu},
                                    {"uan",pinyin_mb_cuan},
                                    {"ui",pinyin_mb_cui},
                                    {"un",pinyin_mb_cun},
                                    {"uo",pinyin_mb_cuo} };
py_index_t pinyin_index_d[] = { {"a",pinyin_mb_da}, //以前为"a   "则无法显示da
                                    {"ai",pinyin_mb_dai},
                                    {"an",pinyin_mb_dan},
                                    {"ang",pinyin_mb_dang},
                                    {"ao",pinyin_mb_dao},
                                    {"e",pinyin_mb_de},
                                    {"ei",pinyin_mb_dei},
                                    {"eng",pinyin_mb_deng},
                                    {"i",pinyin_mb_di},
                                    {"ia",pinyin_mb_dia},
                                    {"ian",pinyin_mb_dian},
                                    {"iao",pinyin_mb_diao},
                                    {"ie",pinyin_mb_die},
                                    {"ing",pinyin_mb_ding},
                                    {"iu",pinyin_mb_diu},
                                    {"o",pinyin_mb_dong},
                                    {"ong",pinyin_mb_dong},
                                    {"ou",pinyin_mb_dou},
                                    {"u",pinyin_mb_du},
                                    {"ua",pinyin_mb_duan},
                                    {"uan",pinyin_mb_duan},
                                    {"ui",pinyin_mb_dui},
                                    {"un",pinyin_mb_dun},
                                    {"uo",pinyin_mb_duo} };
py_index_t pinyin_index_e[] = { {"",pinyin_mb_e},
                                    {"i",pinyin_mb_ei},
                                    {"n",pinyin_mb_en},
                                    {"r",pinyin_mb_er} };
py_index_t pinyin_index_f[] = { {"a",pinyin_mb_fa},
                                    {"an",pinyin_mb_fan},
                                    {"ang",pinyin_mb_fang},
                                    {"e",pinyin_mb_fei},
                                    {"ei",pinyin_mb_fei},
                                    {"en",pinyin_mb_fen},
                                    {"eng",pinyin_mb_feng},
                                    {"o",pinyin_mb_fo},
                                    {"ou",pinyin_mb_fou},
                                    {"u",pinyin_mb_fu} };
py_index_t pinyin_index_g[] = { {"a",pinyin_mb_ga},
                                    {"ai",pinyin_mb_gai},
                                    {"an",pinyin_mb_gan},
                                    {"ang",pinyin_mb_gang},
                                    {"ao",pinyin_mb_gao},
                                    {"e",pinyin_mb_ge},
                                    {"ei",pinyin_mb_gei},
                                    {"en",pinyin_mb_gan},
                                    {"eng",pinyin_mb_geng},
                                    {"o",pinyin_mb_gong},
                                    {"on",pinyin_mb_gong},
                                    {"ong",pinyin_mb_gong},
                                    {"ou",pinyin_mb_gou},
                                    {"u",pinyin_mb_gu},
                                    {"ua",pinyin_mb_gua},
                                    {"uai",pinyin_mb_guai},
                                    {"uan",pinyin_mb_guan},
                                    {"uang",pinyin_mb_guang},
                                    {"ui",pinyin_mb_gui},
                                    {"un",pinyin_mb_gun},
                                    {"uo",pinyin_mb_guo} };
py_index_t pinyin_index_h[] = { {"a",pinyin_mb_ha},
                                    {"ai",pinyin_mb_hai},
                                    {"an",pinyin_mb_han},
                                    {"ang",pinyin_mb_hang},
                                    {"ao",pinyin_mb_hao},
                                    {"e",pinyin_mb_he},
                                    {"ei",pinyin_mb_hei},
                                    {"en",pinyin_mb_hen},
                                    {"eng",pinyin_mb_heng},
                                    {"o",pinyin_mb_hong},
                                    {"on",pinyin_mb_hong},
                                    {"ong",pinyin_mb_hong},
                                    {"ou",pinyin_mb_hou},
                                    {"u",pinyin_mb_hu},
                                    {"ua",pinyin_mb_hua},
                                    {"uai",pinyin_mb_huai},
                                    {"uan",pinyin_mb_huan},
                                    {"uang",pinyin_mb_huang},
                                    {"ui",pinyin_mb_hui},
                                    {"un",pinyin_mb_hun},
                                    {"uo",pinyin_mb_huo} };
py_index_t pinyin_index_i[] = { {"",pinyin_mb_space} };
py_index_t pinyin_index_j[] = { {"i",pinyin_mb_ji},
                                    {"ia",pinyin_mb_jia},
                                    {"ian",pinyin_mb_jian},
                                    {"iang",pinyin_mb_jiang},
                                    {"iao",pinyin_mb_jiao},
                                    {"ie",pinyin_mb_jie},
                                    {"in",pinyin_mb_jin},
                                    {"ing",pinyin_mb_jing},
                                    {"iong",pinyin_mb_jiong},
                                    {"iu",pinyin_mb_jiu},
                                    {"u",pinyin_mb_ju},
                                    {"uan",pinyin_mb_juan},
                                    {"ue",pinyin_mb_jue},
                                    {"un",pinyin_mb_jun} };
py_index_t pinyin_index_k[] = { {"a",pinyin_mb_ka},
                                    {"ai",pinyin_mb_kai},
                                    {"an",pinyin_mb_kan},
                                    {"ang",pinyin_mb_kang},
                                    {"ao",pinyin_mb_kao},
                                    {"e",pinyin_mb_ke},
                                    {"en",pinyin_mb_ken},
                                    {"eng",pinyin_mb_keng},
                                    {"o",pinyin_mb_kong},
                                    {"on",pinyin_mb_kong},
                                    {"ong",pinyin_mb_kong},
                                    {"ou",pinyin_mb_kou},
                                    {"u",pinyin_mb_ku},
                                    {"ua",pinyin_mb_kua},
                                    {"uai",pinyin_mb_kuai},
                                    {"uan",pinyin_mb_kuan},
                                    {"uang",pinyin_mb_kuang},
                                    {"ui",pinyin_mb_kui},
                                    {"un",pinyin_mb_kun},
                                    {"uo",pinyin_mb_kuo} };
py_index_t pinyin_index_l[] = { {"a",pinyin_mb_la},
                                    {"ai",pinyin_mb_lai},
                                    {"an",pinyin_mb_lan},
                                    {"ang",pinyin_mb_lang},
                                    {"ao",pinyin_mb_lao},
                                    {"e",pinyin_mb_le},
                                    {"ei",pinyin_mb_lei},
                                    {"eng",pinyin_mb_leng},
                                    {"i",pinyin_mb_li},
                                    {"ia",pinyin_mb_lia},
                                    {"ian",pinyin_mb_lian},
                                    {"iang",pinyin_mb_liang},
                                    {"iao",pinyin_mb_liao},
                                    {"ie",pinyin_mb_lie},
                                    {"in",pinyin_mb_lin},
                                    {"ing",pinyin_mb_ling},
                                    {"iu",pinyin_mb_liu},
                                    {"o",pinyin_mb_lo},
                                    {"on",pinyin_mb_long},
                                    {"ong",pinyin_mb_long},
                                    {"ou",pinyin_mb_lou},
                                    {"u",pinyin_mb_lu},
                                    {"ua",pinyin_mb_luan},
                                    {"uan",pinyin_mb_luan},
                                    {"ue",pinyin_mb_lue},
                                    {"un",pinyin_mb_lun},
                                    {"uo",pinyin_mb_luo},
                                    {"v",pinyin_mb_lv} };
py_index_t pinyin_index_m[] = { {"a",pinyin_mb_ma},
                                    {"ai",pinyin_mb_mai},
                                    {"an",pinyin_mb_man},
                                    {"ang",pinyin_mb_mang},
                                    {"ao",pinyin_mb_mao},
                                    {"e",pinyin_mb_me},
                                    {"ei",pinyin_mb_mei},
                                    {"en",pinyin_mb_men},
                                    {"eng",pinyin_mb_meng},
                                    {"i",pinyin_mb_mi},
                                    {"ian",pinyin_mb_mian},
                                    {"iao",pinyin_mb_miao},
                                    {"ie",pinyin_mb_mie},
                                    {"in",pinyin_mb_min},
                                    {"ing",pinyin_mb_ming},
                                    {"iu",pinyin_mb_miu},
                                    {"o",pinyin_mb_mo},
                                    {"ou",pinyin_mb_mou},
                                    {"u",pinyin_mb_mu} };
py_index_t pinyin_index_n[] = { {"a",pinyin_mb_na},
                                    {"ai",pinyin_mb_nai},
                                    {"an",pinyin_mb_nan},
                                    {"ang",pinyin_mb_nang},
                                    {"ao",pinyin_mb_nao},
                                    {"e",pinyin_mb_ne},
                                    {"ei",pinyin_mb_nei},
                                    {"en",pinyin_mb_nen},
                                    {"eng",pinyin_mb_neng},
                                    {"g",pinyin_mb_ng},
                                    {"i",pinyin_mb_ni},
                                    {"ia",pinyin_mb_nian},
                                    {"ian",pinyin_mb_nian},
                                    {"iang",pinyin_mb_niang},
                                    {"iao",pinyin_mb_niao},
                                    {"ie",pinyin_mb_nie},
                                    {"in",pinyin_mb_nin},
                                    {"ing",pinyin_mb_ning},
                                    {"iu",pinyin_mb_niu},
                                    {"ong",pinyin_mb_nong},
                                    {"ou",pinyin_mb_nou},
                                    {"u",pinyin_mb_nu},
                                    {"uan",pinyin_mb_nuan},
                                    {"ue",pinyin_mb_nue},
                                    {"uo",pinyin_mb_nuo},
                                    {"v",pinyin_mb_nv} };
py_index_t pinyin_index_o[] = { {"",pinyin_mb_o},
                                    {"u",pinyin_mb_ou} };
py_index_t pinyin_index_p[] = { {"a",pinyin_mb_pa},
                                    {"ai",pinyin_mb_pai},
                                    {"an",pinyin_mb_pan},
                                    {"ang",pinyin_mb_pang},
                                    {"ao",pinyin_mb_pao},
                                    {"ei",pinyin_mb_pei},
                                    {"en",pinyin_mb_pen},
                                    {"eng",pinyin_mb_peng},
                                    {"i",pinyin_mb_pi},
                                    {"ia",pinyin_mb_pian},
                                    {"ian",pinyin_mb_pian},
                                    {"iao",pinyin_mb_piao},
                                    {"ie",pinyin_mb_pie},
                                    {"in",pinyin_mb_pin},
                                    {"ing",pinyin_mb_ping},
                                    {"o",pinyin_mb_po},
                                    {"ou",pinyin_mb_pou},
                                    {"u",pinyin_mb_pu} };
py_index_t pinyin_index_q[] = { {"i",pinyin_mb_qi},
                                    {"ia",pinyin_mb_qia},
                                    {"ian",pinyin_mb_qian},
                                    {"iang",pinyin_mb_qiang},
                                    {"iao",pinyin_mb_qiao},
                                    {"ie",pinyin_mb_qie},
                                    {"in",pinyin_mb_qin},
                                    {"ing",pinyin_mb_qing},
                                    {"iong",pinyin_mb_qiong},
                                    {"iu",pinyin_mb_qiu},
                                    {"u",pinyin_mb_qu},
                                    {"ua",pinyin_mb_quan},
                                    {"uan",pinyin_mb_quan},
                                    {"ue",pinyin_mb_que},
                                    {"ui",pinyin_mb_qui},
                                    {"un",pinyin_mb_qun} };
py_index_t pinyin_index_r[] = {
    {"a",pinyin_mb_ran},
    {"an",pinyin_mb_ran},
                                    {"ang",pinyin_mb_rang},
                                    {"ao",pinyin_mb_rao},
                                    {"e",pinyin_mb_re},
                                    {"en",pinyin_mb_ren},
                                    {"eng",pinyin_mb_reng},
                                    {"i",pinyin_mb_ri},
                                    {"o",pinyin_mb_rong},
                                    {"on",pinyin_mb_rong},
                                    {"ong",pinyin_mb_rong},
                                    {"ou",pinyin_mb_rou},
                                    {"u",pinyin_mb_ru},
                                    {"ua",pinyin_mb_ruan},
                                    {"uan",pinyin_mb_ruan},
                                    {"ui",pinyin_mb_rui},
                                    {"un",pinyin_mb_run},
                                    {"uo",pinyin_mb_ruo} };
py_index_t pinyin_index_s[] = { {"a",pinyin_mb_sa},
                                    {"ai",pinyin_mb_sai},
                                    {"an",pinyin_mb_san},
                                    {"ang",pinyin_mb_sang},
                                    {"ao",pinyin_mb_sao},
                                    {"e",pinyin_mb_se},
                                    {"en",pinyin_mb_sen},
                                    {"eng",pinyin_mb_seng},
                                    {"h",pinyin_mb_sha},
                                    {"ha",pinyin_mb_sha},
                                    {"hai",pinyin_mb_shai},
                                    {"han",pinyin_mb_shan},
                                    {"hang",pinyin_mb_shang},
                                    {"hao",pinyin_mb_shao},
                                    {"he",pinyin_mb_she},
                                    {"hei",pinyin_mb_shei},
                                    {"hen",pinyin_mb_shen},
                                    {"heng",pinyin_mb_sheng},
                                    {"hi",pinyin_mb_shi},
                                    {"hou",pinyin_mb_shou},
                                    {"hu",pinyin_mb_shu},
                                    {"hua",pinyin_mb_shua},
                                    {"huai",pinyin_mb_shuai},
                                    {"huan",pinyin_mb_shuan},
                                    {"huang",pinyin_mb_shuang},
                                    {"hui",pinyin_mb_shui},
                                    {"hun",pinyin_mb_shun},
                                    {"huo",pinyin_mb_shuo},
                                    {"i",pinyin_mb_si},
                                    {"o",pinyin_mb_song},
                                    {"on",pinyin_mb_song},
                                    {"ong",pinyin_mb_song},
                                    {"ou",pinyin_mb_sou},
                                    {"u",pinyin_mb_su},
                                    {"uan",pinyin_mb_suan},
                                    {"ui",pinyin_mb_sui},
                                    {"un",pinyin_mb_sun},
                                    {"uo",pinyin_mb_suo} };
py_index_t pinyin_index_t[] = { {"a",pinyin_mb_ta},
                                    {"ai",pinyin_mb_tai},
                                    {"an",pinyin_mb_tan},
                                    {"ang",pinyin_mb_tang},
                                    {"ao",pinyin_mb_tao},
                                    {"e",pinyin_mb_te},
                                    {"eng",pinyin_mb_teng},
                                    {"i",pinyin_mb_ti},
                                    {"ia",pinyin_mb_tian},
                                    {"ian",pinyin_mb_tian},
                                    {"iao",pinyin_mb_tiao},
                                    {"ie",pinyin_mb_tie},
                                    {"in",pinyin_mb_ting},
                                    {"ing",pinyin_mb_ting},
                                    {"ong",pinyin_mb_tong},
                                    {"ou",pinyin_mb_tou},
                                    {"u",pinyin_mb_tu},
                                    {"ua",pinyin_mb_tuan},
                                    {"uan",pinyin_mb_tuan},
                                    {"ui",pinyin_mb_tui},
                                    {"un",pinyin_mb_tun},
                                    {"uo",pinyin_mb_tuo} };
py_index_t pinyin_index_u[] = { {"",pinyin_mb_space} };
py_index_t pinyin_index_v[] = { {"",pinyin_mb_space} };
py_index_t pinyin_index_w[] = { {"a",pinyin_mb_wa},
                                    {"ai",pinyin_mb_wai},
                                    {"an",pinyin_mb_wan},
                                    {"ang",pinyin_mb_wang},
                                    {"e",pinyin_mb_wei},
                                    {"ei",pinyin_mb_wei},
                                    {"en",pinyin_mb_wen},
                                    {"eng",pinyin_mb_weng},
                                    {"o",pinyin_mb_wo},
                                    {"u",pinyin_mb_wu} };
py_index_t pinyin_index_x[] = { {"i",pinyin_mb_xi},
                                    {"ia",pinyin_mb_xia},
                                    {"ian",pinyin_mb_xian},
                                    {"iang",pinyin_mb_xiang},
                                    {"iao",pinyin_mb_xiao},
                                    {"ie",pinyin_mb_xie},
                                    {"in",pinyin_mb_xin},
                                    {"ing",pinyin_mb_xing},
                                    {"iong",pinyin_mb_xiong},
                                    {"iu",pinyin_mb_xiu},
                                    {"u",pinyin_mb_xu},
                                    {"ua",pinyin_mb_xuan},
                                    {"uan",pinyin_mb_xuan},
                                    {"ue",pinyin_mb_xue},
                                    {"un",pinyin_mb_xun} };
py_index_t pinyin_index_y[] = { {"a",pinyin_mb_ya},
                                    {"an",pinyin_mb_yan},
                                    {"ang",pinyin_mb_yang},
                                    {"ao",pinyin_mb_yao},
                                    {"e",pinyin_mb_ye},
                                    {"i",pinyin_mb_yi},
                                    {"in",pinyin_mb_yin},
                                    {"ing",pinyin_mb_ying},
                                    {"o",pinyin_mb_yo},
                                    {"on",pinyin_mb_yong},
                                    {"ong",pinyin_mb_yong},
                                    {"ou",pinyin_mb_you},
                                    {"u",pinyin_mb_yu},
                                    {"ua",pinyin_mb_yuan},
                                    {"ua",pinyin_mb_yuan},
                                    {"uan",pinyin_mb_yuan},
                                    {"ue",pinyin_mb_yue},
                                    {"un",pinyin_mb_yun} };
py_index_t pinyin_index_z[] = { {"a",pinyin_mb_za},
                                    {"ai",pinyin_mb_zai},
                                    {"an",pinyin_mb_zan},
                                    {"ang",pinyin_mb_zang},
                                    {"ao",pinyin_mb_zao},
                                    {"e",pinyin_mb_ze},
                                    {"ei",pinyin_mb_zei},
                                    {"en",pinyin_mb_zen},
                                    {"eng",pinyin_mb_zeng},
                                    {"h",pinyin_mb_zha},
                                    {"ha",pinyin_mb_zha},
                                    {"hai",pinyin_mb_zhai},
                                    {"han",pinyin_mb_zhan},
                                    {"hang",pinyin_mb_zhang},
                                    {"hao",pinyin_mb_zhao},
                                    {"he",pinyin_mb_zhe},
                                    {"hen",pinyin_mb_zhen},
                                    {"heng",pinyin_mb_zheng},
                                    {"hi",pinyin_mb_zhi},
                                    {"hong",pinyin_mb_zhong},
                                    {"hou",pinyin_mb_zhou},
                                    {"hu",pinyin_mb_zhu},
                                    {"hua",pinyin_mb_zhua},
                                    {"huai",pinyin_mb_zhuai},
                                    {"huan",pinyin_mb_zhuan},
                                    {"huang",pinyin_mb_zhuang},
                                    {"hui",pinyin_mb_zhui},
                                    {"hun",pinyin_mb_zhun},
                                    {"huo",pinyin_mb_zhuo},
                                    {"i",pinyin_mb_zi},
                                    {"on",pinyin_mb_zong},
                                    {"ong",pinyin_mb_zong},
                                    {"ou",pinyin_mb_zou},
                                    {"u",pinyin_mb_zu},
                                    {"ua",pinyin_mb_zuan},
                                    {"uan",pinyin_mb_zuan},
                                    {"ui",pinyin_mb_zui},
                                    {"un",pinyin_mb_zun},
                                    {"uo",pinyin_mb_zuo} };
py_index_t pinyin_index_end[] = { {"",pinyin_mb_space} };


/*定义首字母索引表*/
py_index_t* pinyin_index_headletter[] = { pinyin_index_a,
                                        pinyin_index_b,
                                        pinyin_index_c,
                                        pinyin_index_d,
                                        pinyin_index_e,
                                        pinyin_index_f,
                                        pinyin_index_g,
                                        pinyin_index_h,
                                        pinyin_index_i,
                                        pinyin_index_j,
                                        pinyin_index_k,
                                        pinyin_index_l,
                                        pinyin_index_m,
                                        pinyin_index_n,
                                        pinyin_index_o,
                                        pinyin_index_p,
                                        pinyin_index_q,
                                        pinyin_index_r,
                                        pinyin_index_s,
                                        pinyin_index_t,
                                        pinyin_index_u,
                                        pinyin_index_v,
                                        pinyin_index_w,
                                        pinyin_index_x,
                                        pinyin_index_y,
                                        pinyin_index_z,
                                        pinyin_index_end };


#define LEN(a) sizeof(a)/sizeof(a[0])
unsigned index_number[] = {
    LEN(pinyin_index_a), //a
    LEN(pinyin_index_b),//b
    LEN(pinyin_index_c),//c
    LEN(pinyin_index_d),//d
    LEN(pinyin_index_e), //e
    LEN(pinyin_index_f), //f
    LEN(pinyin_index_g),//g
    LEN(pinyin_index_h),//h
    LEN(pinyin_index_i), //i
    LEN(pinyin_index_j),//j
    LEN(pinyin_index_k),//k
    LEN(pinyin_index_l),//l
    LEN(pinyin_index_m),//m
    LEN(pinyin_index_n),//n
    LEN(pinyin_index_o), //o
    LEN(pinyin_index_p),//p
    LEN(pinyin_index_q),//q
    LEN(pinyin_index_r),//r
    LEN(pinyin_index_s),//s
    LEN(pinyin_index_t),//t
    LEN(pinyin_index_u), //u
    LEN(pinyin_index_v), //v
    LEN(pinyin_index_w), //w
    LEN(pinyin_index_x),//x
    LEN(pinyin_index_y),//y
    LEN(pinyin_index_z),//z
};

/*
*********************************************************************************************************
*	函 数 名: PYSearch
*	功能说明: 检索拼音的函数,使用很简单，只需输入拼音就行返回这个拼音对应的汉字个数。
*	形    strInput_py_str   拼音字符串
*        num   返回此拼音对应的汉字个数
*	返 回 值: 如果这个拼音存在汉字与其对应，返回检索到的汉字的指针，如果没有，返回空指针
*********************************************************************************************************
*/
const char* pinyin_search(char* strInput_py_str, int* num)
{
    py_index_t* cpHZ;
    char i, cInputStrLength = 0;
    volatile unsigned char count = 0;

    if(*strInput_py_str == '\0') return NULL;         /*如果输入空字符返回0*/

    if(*strInput_py_str == 'i') return NULL;          /*错误拼音输入*/
    if(*strInput_py_str == 'u') return NULL;
    if(*strInput_py_str == 'v') return NULL;

    //    cInputStrLength = strlen(strInput_py_str);        /*输入拼音串长度*/
    while(strInput_py_str[cInputStrLength] != 0) cInputStrLength++;			  /* 计算检索的拼音的字节数     */

// 本来就是小写字母,所以无需再转换了
//    for(i = 0; i < cInputStrLength; i++)
//    {
//        *(strInput_py_str+i) |= 0x20;                 // 将字母串转为小写 ,目前输入的本身就是小写字母,所以此处无需再转换了
//    }

    cpHZ = pinyin_index_headletter[strInput_py_str[0] - 'a'];              /*查首字母索引*/
    count = index_number[strInput_py_str[0] - 'a'];
    //    cpHZedge = pinyin_index_t_headletter[strInput_py_str[0] - 'a' + 1];     /*设置指针界限*/
    //    printf("%x, %x\n", cpHZ, cpHZedge);
    strInput_py_str++;                              /*指向拼音串第二个字母*/

    while(count--)                                  /*索引表不超界*/
    {
        for(i = 0; i < cInputStrLength; i++)
        {
            if(*(strInput_py_str + i) != *((cpHZ->py) + i))
                break;                              /*发现字母串不配,退出*/
        }
        if(cInputStrLength == 1 || i == cInputStrLength)                    /*字母串全配*/
        {
#if   USER_UNICODE_MODE == USER_UNICODE_UTF8
            // 特别注意下面这个函数，因为UTF-8编码格式的汉字是3个字节 
            * num = strlen((const char*)(*cpHZ).py_mb) / 3;
#else  //if   USER_UNICODE_MODE == USER_UNICODE_GBK2312
            // 使用GBK2312的汉字是2个字节 
            * num = strlen((const char*)(*cpHZ).pinyin_mb) / 2;
#endif
            return (char*)((*cpHZ).py_mb);  // ok
//          return (char *)(cpHZ->pinyin_mb);  // ok
        }
        cpHZ++;
    }
    return NULL;                                    /*无果而终*/

}





