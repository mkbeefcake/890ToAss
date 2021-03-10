#include "LanguageAutoDetect.h"
#include "StringExtensions.h"


std::vector<std::string> LanguageAutoDetect::AutoDetectWordsEnglish = { "we", "are", "and", "your", "what", "[TW]hat's", "You're", "(any|some|every)thing", "money", "because", "human", "because", "welcome", "really", "something", "confusing", "about", "know", "people", "other", "which", "would", "these", "could" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsDanish = { "vi", "han", "og", "jeg", "var", "men", "gider", "bliver", "virkelig", "kommer", "tilbage", "Hej", "længere", "gjorde", "dig", "havde", "[Uu]ndskyld", "arbejder", "vidste", "troede", "stadigvæk", "[Mm]åske", "første", "gik", "fortælle", "begyndt", "spørgsmål", "pludselig" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsNorwegian = { "vi", "og", "jeg", "var", "men", "igjen", "Nei", "Hei", "noen", "gjøre", "kanskje", "[Tt]renger", "tenker", "skjer", "møte", "veldig", "takk", "penger", "konsept", "hjelp", "forsvunnet", "skutt", "sterkt", "minste", "første", "fortsette", "inneholder", "gikk", "fortelle", "begynt", "spørsmål", "plutselig" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsSwedish = { "vi", "är", "och", "Jag", "inte", "för", "måste", "Öppna", "Förlåt", "nånting", "ingenting", "jävla", "Varför", "[Ss]nälla", "fattar", "själv", "säger", "öppna", "jävligt", "dörren", "göra", "behöver", "tillbaka", "Varför", "träffa", "kanske", "säga", "hände", "honom", "hennes", "veckor", "tänker", "själv", "pratar", "mycket", "mamma", "dödade", "Ursäkta", "säger", "senaste", "håller", "förstår", "veckan", "varför", "tycker", "första", "gick", "berätta", "börjat", "människor", "frågor", "fråga", "plötsligt", "skämt" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsSpanish = { "qué", "eso", "muy", "estoy?", "ahora", "hay", "tú", "así", "cuando", "cómo", "él", "sólo", "quiero", "gracias", "puedo", "bueno", "soy", "hacer", "fue", "eres", "usted", "tienes", "puede", "[Ss]eñor", "ese", "voy", "quién", "creo", "hola", "dónde", "sus", "verdad", "quieres", "mucho", "entonces", "estaba", "tiempo", "esa", "mejor", "hombre", "hace", "dios", "también", "están", "siempre", "hasta", "ahí", "siento", "puedes" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsItalian = { "Buongiorno", "Grazie", "Cosa", "quest[ao]", "quell[ao]", "tutt[io]", "[st]uo", "qualcosa", "ancora", "sono", "bene", "più", "andare", "essere", "venire", "abbiamo", "andiamo", "ragazzi", "signore", "numero", "giorno", "propriamente", "sensitivo", "negativo", "davvero", "faccio", "voglio", "vuole", "perché", "allora", "niente", "anche", "stai", "detto", "fatto", "hanno", "molto", "stato", "siamo", "così", "vuoi", "noi", "vero", "loro", "fare", "gli", "due" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsFrench = { "pas", "[vn]ous", "ça", "une", "pour", "[mt]oi", "dans", "elle", "tout", "plus", "[bmt]on", "suis", "avec", "oui", "fait", "ils", "être", "faire", "comme", "était", "quoi", "ici", "veux", "vouloir", "quelque", "pouvoir", "rien", "dit", "où", "votre", "pourquoi", "sont", "cette", "peux", "alors", "comment", "avez", "très", "même", "merci", "ont", "aussi", "chose", "voir", "allez", "tous", "ces", "deux", "avoir", " pouvoir", "même", "œil", "sœur" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsPortuguese = { "[Nn]ão", "[Ee]ntão", "uma", "ele", "bem", "isso", "você", "sim", "meu", "muito", "estou", "ela", "fazer", "tem", "já", "minha", "tudo", "só", "tenho", "agora", "vou", "seu", "quem", "há", "lhe", "quero", "nós", "são", "ter", "coisa", "dizer", "eles", "pode", "bom", "mesmo", "mim", "estava", "assim", "estão", "até", "quer", "temos", "acho", "obrigado", "também", "tens", "deus", "quê", "ainda", "noite", "conversar", "Desculpe", "verdade" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsGerman = { "und", "auch", "sich", "bin", "hast", "möchte", "müssen", "weiß", "[Vv]ielleicht", "Warum", "jetzt", "Verdammt", "bist", "Darum", "sitzt", "Setz", "Das ist", "Du bist", "nicht", "Scheiße", "Nein", "für", "gesagt", "zwei", "richtig" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsDutch = { "van", "een", "[Hh]et", "m(ij|ĳ)", "z(ij|ĳ)n", "hebben", "alleen", "Waarom" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsPolish = { "Czy", "ale", "ty", "siê", "się", "jest", "mnie", "Proszę", "życie", "statku", "życia", "Czyli", "Wszystko", "Wiem", "Przepraszam", "dobrze", "chciałam", "Dziękuję", "Żołnierzyk", "Łowca", "został", "stało", "dolarów", "wiadomości", "Dobrze", "będzie", "Dzień", "przyszłość", "Uratowałaś", "Cześć", "Trzeba", "zginąć", "walczyć", "ludzkość", "maszyny", "Jeszcze", "okrążenie", "wyścigu", "porządku", "detektywie", "przebieralni", "który" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsGreek = { "μου", "[Εε]ίναι", "αυτό", "Τόμπυ", "καλά", "Ενταξει", "πρεπει", "Λοιπον", "τιποτα", "ξερεις" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsRussian = { "[Ээч]?то", "[Нн]е", "[ТтМмбв]ы", "Да", "[Нн]ет", "Он", "его", "тебя", "как", "меня", "Но", "всё", "мне", "вас", "знаю", "ещё", "за", "нас", "чтобы", "был" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsBulgarian = { "[Кк]акво", "тук", "може", "Как", "Да", "Ваше", "нещо", "беше", "Добре", "трябва", "става", "Джоузи", "Защо", "дяволите", "Сиянието", "Трябва", "години", "Стивън", "Благодаря" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsUkrainian = { "[Нн]і", "[Пп]ривіт", "[Цц]е", "[Щщ]о", "[Йй]ого", "[Вв]ін", "[Яя]к", "[Гг]аразд", "[Яя]кщо", "[Мм]ені", "[Тт]вій", "[Її]х", "[Вв]ітаю", "[Дд]якую", "вже", "було", "був", "цього", "нічого", "немає", "може", "знову", "бо", "щось", "щоб", "цим", "тобі", "хотів", "твоїх", "мої", "мій", "має", "їм", "йому", "дуже" };


std::vector<std::string> LanguageAutoDetect::AutoDetectWordsAlbanian = { "është", "këtë", "Unë", "mirë", "shumë", "Çfarë", "çfarë", "duhet", "Është", "mbrapa", "Faleminderit", "vërtet", "diçka", "gjithashtu", "gjithe", "eshte", "shume", "vetem", "tënde", "çmendur", "vullnetin", "vdekur" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsArabic = { "من", "هل", "لا", "في", "لقد", "ما", "ماذا", "يا", "هذا", "إلى", "على", "أنا", "أنت", "حسناً", "أيها", "كان", "كيف", "يكون", "هذه", "هذان", "الذي", "التي", "الذين", "هناك", "هنالك" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsFarsi = { "این", "برای", "اون", "سیب", "کال", "رو", "خيلي", "آره", "بود", "اون", "نيست", "اينجا", "باشه", "سلام", "ميکني", "داري", "چيزي", "چرا", "خوبه" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsHebrew = { "אתה", "אולי", "הוא", "בסדר", "יודע", "טוב" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsVietnamese = { "không", "[Tt]ôi", "anh", "đó", "ông", "tôi", "phải", "người", "được", "Cậu", "chúng", "chuyện", "muốn", "những", "nhiều" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsHungarian = { "hogy", "lesz", "tudom", "vagy", "mondtam", "még", "vagyok", "csak", "Hát", "felesége", "Csak", "utána", "jött", "Miért", "Akkor", "magát", "holnap", "Tudja", "Köszönöm", "élet", "Örvendek", "vissza", "hogy", "tudom", "Rendben", "Istenem", "Gyerünk", "értem", "vagyok", "hiszem", "történt", "rendben", "olyan", "őket", "vannak", "mindig", "Kérlek", "Gyere", "kicsim", "vagyunk" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsTurkish = { "için", "Tamam", "Hayır", "benim", "daha", "deðil", "önce", "lazým", "çalýþýyor", "Aldırma", "burada", "efendim", "şey", "çok", "Çok", "için", "Merhaba", "Evet", "kötü", "musun", "güzel", "çünkü", "büyük", "Bebeğim", "olduğunu", "istiyorum", "değilsin", "bilmiyorum", "otursana", "Selam", "Tabii","konuda","istiyor","Tetekkürler", "istemiyorum", "Gerçekte" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsCroatianAndSerbian = { "sam", "ali", "nije", "Nije", "samo", "ovo", "kako", "dobro", "Dobro", "sve", "tako", "će", "mogu", "ću", "zašto", "nešto", "za", "misliš", "možeš", "možemo", "ništa", "znaš", "ćemo", "znam" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsCroatian = { "što", "ovdje", "gdje", "kamo", "tko", "prije", "uvijek", "vrijeme", "vidjeti", "netko", "vidio", "nitko", "bok", "lijepo", "oprosti", "htio", "mjesto", "oprostite", "čovjek", "dolje", "čovječe", "dvije", "dijete", "dio", "poslije", "događa", "vjerovati", "vjerojatno", "vjerujem", "točno", "razumijem", "vidjela", "cijeli", "svijet", "obitelj", "volio", "sretan", "dovraga", "svijetu", "htjela", "vidjeli", "negdje", "želio", "ponovno", "djevojka", "umrijeti", "čovjeka", "mjesta", "djeca", "osjećam", "uopće", "djecu", "naprijed", "obitelji", "doista", "mjestu", "lijepa", "također", "riječ", "tijelo" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsSerbian = { "šta", "ovde", "gde", "ko", "pre", "uvek", "vreme", "videti", "neko", "video", "niko", "ćao", "lepo", "izvini", "hteo", "mesto", "izvinite", "čovek", "dole", "čoveče", "dve", "dete", "deo", "posle", "dešava", "verovati", "verovatno", "verujem", "tačno", "razumem", "videla", "ceo", "svet", "porodica", "voleo", "srećan", "dođavola", "svetu", "htela", "videli", "negde", "želeo", "ponovo", "devojka", "umreti", "čoveka", "mesta", "deca", "osećam", "uopšte", "decu", "napred", "porodicu", "zaista", "mestu", "lepa", "takođe", "reč", "telo" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsSerbianCyrillic = { "сам", "али", "није", "само", "ово", "како", "добро", "све", "тако", "ће", "могу", "ћу", "зашто", "нешто", "за", "шта", "овде", "бити", "чини", "учениче", "побегне", "остати", "Један", "Назад", "Молим" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsIndonesian = { "yang", "tahu", "bisa", "akan", "tahun", "tapi", "dengan", "untuk", "rumah", "dalam", "sudah", "bertemu" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsThai = { "ผู้กอง", "โรเบิร์ต", "วิตตอเรีย", "เข้าใจมั้ย", "คุณตำรวจ", "ราเชล", "เพื่อน", "เลดดิส", "พระเจ้า", "เท็ดดี้", "หัวหน้า", "แอนดรูว์", "ขอโทษครับ", "ขอบคุณ", "วาร์กัส", "ทุกคน", "ไม่เอาน่า", "อิซานะ", "มจริง", "รับทราบ", "พอคะ", "ครับ", "อยาตขาป", "ยินดีทีดรูจักคะ", "ปลอดภัยดีนะ", "ทุกคน", "ตอนที", "ขอบคุณครับ", "ขอทษนะคะ", "ขอทษคะ" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsKorean = { "사루", "거야", "엄마", "그리고", "아니야", "하지만", "말이야", "그들은", "우리가", "엄마가", "괜찮아", "일어나", "잘했어", "뭐라고", "있어요", "있어요", "보여줘", "괜찮아요", "목소릴", "기억이", "저주를", "좋아요" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsMacedonian = { "господине", "Нема", "господине", "работа", "вселената", "Може", "треба", "Треба", "слетување", "капсулата", "време", "Френдшип", "Прием", "Добро", "пресметки", "Благодарам", "нешто", "Благодарам", "орбитата", "инженер", "Харисон", "Фала", "тоалет", "орбита", "знаеме", "Супервизор", "жени", "Добра", "требаат", "што", "дeкa", "eшe", "кучe", "Руиз", "кучeто", "кучињa", "Бјути", "имa", "многу", "кучињaтa", "AДЗЖ", "Животни", "моЖe", "мaчe", "мecто", "имaмe", "мaчињa", "пpвото", "пpaвaт", "нeшто", "колку" };


std::vector<std::string> LanguageAutoDetect::AutoDetectWordsFinnish = { "että", "kuin", "minä", "mitään", "Mutta", "siitä", "täällä", "poika", "Kiitos", "enää", "vielä", "tässä", "sulkeutuu", "Soitetaan", "Soita", "Onnistui", "Mitä", "Etuovi", "tippiä", "antaa", "Onko", "Hidasta", "tuntia", "tilata", "päästä", "palolaitokselle", "hätänumeroon", "aikaa", "Tämä", "Sinulla", "Palauttaa", "Kiitos", "Arvostele", "Älä", "toimi", "televisiota", "takaisin", "reitin", "pitäisi", "palauttaa", "nopeamman", "mitään", "meidät", "maksaa", "kuullut", "kaikki", "jälkeen", "ihmiset", "hätäkeskukseen", "hiljaa", "haluat", "enää", "enemmän", "auttaa", "Tunkeilijahälytys", "Pysähdy", "Princen", "Käänny", "Kyllä", "Kiva", "Haluatko", "Haluan" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsRomanian = { "pentru", "oamenii", "decât", "[Vv]reau", "[Ss]înt", "Asteaptã", "Fãrã", "aici", "domnule", "trãiascã", "niciodatã", "înseamnã", "vorbesti", "fãcut", "spune", "făcut", "când", "aici", "Asta", "văzut", "dacă", "câteva", "amândoi", "Când", "totuși", "mașină", "aceeași", "întâmplat", "niște", "ziua", "noastră", "cunoscut", "decat", "[Tt]rebuie", "[Aa]cum", "Poate", "vrea", "soare", "nevoie", "daca", "echilibrul", "vorbesti", "zeului", "atunci", "memoria", "soarele" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsCzechAndSlovak = { "[Oo]n[ao]?", "[Jj]?si", "[Aa]le", "[Tt]en(to)?", "[Rr]ok", "[Tt]ak", "[Aa]by", "[Tt]am", "[Jj]ed(en|na|no)", "[Nn]ež", "[Aa]ni", "[Bb]ez", "[Dd]obr[ýáé]", "[Vv]šak", "[Cc]el[ýáé]", "[Nn]ov[ýáé]", "[Dd]ruh[ýáé]", "jsem", "poøádku", "Pojïme", "háje", "není", "Jdeme", "všecko", "jsme", "Prosím", "Vezmi", "když", "Takže", "Dìkuji", "prechádzku", "všetko", "Poïme", "potom", "Takže", "Neviem", "budúcnosti", "trochu" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsCzech = { ".*[Řř].*", ".*[ůě].*", "[Bb]ýt", "[Jj]sem", "[Jj]si", "[Jj]á", "[Mm]ít", "[Aa]no", "[Nn]e", "[Nn]ic", "[Dd]en", "[Jj]en", "[Cc]o", "[Jj]ak[o]?", "[Nn]ebo", "[Pp]ři", "[Pp]ro", "[Pp]řed.*", "[Jj](ít|du|de|deme|dou)", "[Mm]ezi", "[Jj]eště", "[Čč]lověk", "[Pp]odle", "[Dd]alší" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsSlovak = { ".*[Ôô].*", ".*[ä].*", "[Bb]yť", "[Ss]om", "[Ss]i", "[Jj]a", "[Mm]ať", "[Áá]no", "[Nn]ie", "[Nn]ič", "[Dd]eň", "[Ll]en", "[Čč]o", "[Aa]ko", "[Aa]?[Ll]ebo", "[Pp]ri", "[Pp]re", "[Pp]red.*", "([Íí]sť|[Ii](dem|de|deme|dú))", "[Mm]edzi", "[Ee]šte", "[Čč]lovek", "[Pp]odľa", "[Ďď]alš(í|ia|ie)" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsLatvian = { "Paldies", "neesmu ", "nezinu", "viòð", "viņš", "viņu", "kungs", "esmu", "Viņš", "Velns", "viņa", "dievs", "Pagaidi", "varonis", "agrāk", "varbūt" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsLithuanian = { "tavęs", "veidai", "apie", "jums", "Veidai", "Kaip", "kaip", "reikia", "Šūdas", "frensis", "Ačiū", "vilsonai", "Palauk", "Veidas", "viskas", "Tikrai", "manęs", "Tačiau", "žmogau", "Flagai", "Prašau", "Džiune", "Nakties", "šviesybe", "Supratau", "komanda", "reikia", "apie", "Kodėl", "mūsų", "Ačiū", "vyksta" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsHindi = { "एक", "और", "को", "का", "यह", "सकते", "लिए", "करने", "भारतीय", "सकता", "भारत", "तकनीक", "कंप्यूटिंग", "उपकरण", "भाषाओं", "भाषा", "कंप्यूटर", "आप", "आपको", "अपने", "लेकिन", "करना", "सकता", "बहुत", "चाहते", "अच्छा", "वास्तव", "लगता", "इसलिए", "शेल्डन", "धन्यवाद।", "तरह", "करता", "चाहता", "कोशिश", "करते", "किया", "अजीब", "सिर्फ", "शुरू" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsUrdu = { "نہیں", "ایک", "ہیں", "کیا", "اور", "لئے", "ٹھیک", "ہوں", "مجھے", "تھا", "کرنے", "صرف", "ارے", "یہاں", "بہت", "لیکن", "ساتھ", "اپنے", "اچھا", "میرے", "چاہتا", "انہوں", "تمہیں" };
std::vector<std::string> LanguageAutoDetect::AutoDetectWordsSinhalese = { "කරන්න", "නැහැ", "කියල", "මගේ", "එයා", "ඔයාට", "කැප්ටන්", "ඔයාගේ", "පුළුවන්", "හැම", "වගේ", "වෙන්න", "ඕනා", "නෙමේ", "තියෙන්නේ", "වගේම", "දන්නවා", "වෙනවා", "එහෙම", "හිතන්නේ", "කියලා", "කරනවා", "යන්න", "දෙයක්", "තියනවා", "හොදයි", "දෙන්න", "එකක්", "මොනාද", "කියන්න", "කරන්නේ", "වෙන්නේ", "රොජර්ස්", "දාන්න", "කරලා", "ඔයාව", "වෙලා", "කොහොමද", "කිවුවා", "ඔබට", "රාවුල්" };



int LanguageAutoDetect::GetCount(const std::string &text, std::vector<std::string> &words)
{
/*	auto options = RegexOptions::CultureInvariant | RegexOptions::ExplicitCapture;
	auto pattern = "\\b(" + std::string::Join("|", words) + ")\\b";
	return Regex::Matches(text, pattern, options)->Count;*/

	// to avoid -Wunused-parameter
	UNUSED(text);
	UNUSED(words);
	return 0;

}

int LanguageAutoDetect::GetCountContains(const std::string &text, std::vector<std::string> &words)
{
	int count = 0;
	/*for (auto w : words)
	{
		auto regEx = new Regex(w);
		count += regEx->Matches(text)->Count;

		delete regEx;
	}*/

	// to avoid -Wunused-parameter
	UNUSED(text);
	UNUSED(words);
	return count;
}

std::string LanguageAutoDetect::AutoDetectGoogleLanguage(const std::string &text, int bestCount)
{
	std::string s = LanguageAutoDetect::AutoDetectGoogleLanguage1(text, bestCount);
	if (s != "")
	{
		return s;
	}

	s = LanguageAutoDetect::AutoDetectGoogleLanguage2(text, bestCount);
	if (s != "")
	{
		return s;
	}

	s = LanguageAutoDetect::AutoDetectGoogleLanguage3(text, bestCount);
	if (s != "")
	{
		return s;
	}

	int count = GetCount(text, LanguageAutoDetect::AutoDetectWordsHindi);
	if (count > bestCount)
	{
		return "hi";
	}

	count = GetCount(text, LanguageAutoDetect::AutoDetectWordsUrdu);
	if (count > bestCount)
	{
		return "ur";
	}

	count = GetCount(text, LanguageAutoDetect::AutoDetectWordsSinhalese);
	if (count > bestCount)
	{
		return "sl";
	}

	count = GetCount(text, LanguageAutoDetect::AutoDetectWordsMacedonian);
	if (count > bestCount)
	{
		return "mk";
	}

	return "";
}

std::string LanguageAutoDetect::AutoDetectGoogleLanguageOrNull(Subtitle *subtitle)
{
	auto s = new Subtitle(subtitle);
	s->RemoveEmptyLines();
	auto allText = s->GetAllTexts(500000);
	std::string languageId = AutoDetectGoogleLanguage(allText, s->Paragraphs.size() / 14);
	if (languageId.empty())
	{
		languageId = GetEncodingViaLetter(allText);
	}

	if (languageId.empty())
	{
		languageId = "";
	}

	delete s;
	return languageId;
}

std::string LanguageAutoDetect::GetEncodingViaLetter(const std::string &text)
{
	return GetEncodingViaLetterD(text);
}


std::string LanguageAutoDetect::AutoDetectGoogleLanguage1(const std::string& text, int bestCount)
{
	int count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsEnglish);
	if (count > bestCount)
	{
		int dutchCount = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsDutch);
		if (dutchCount < count)
		{
			return "en";
		}
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsDanish);
	if (count > bestCount)
	{
		std::vector<std::string> word_vec;

		int norwegianCount = LanguageAutoDetect::GetCount(text, word_vec = { "ut", "deg", "meg", "merkelig", "mye", "spørre" });

		int dutchCount = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsDutch);
		int swedishCount = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsSwedish);
		if (norwegianCount < 2 && dutchCount < count && swedishCount < count)
		{
			return "da";
		}
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsNorwegian);
	if (count > bestCount)
	{
		std::vector<std::string> word_vec;

		int danishCount = LanguageAutoDetect::GetCount(text, word_vec = { "siger", "dig", "mig", "mærkelig", "tilbage", "spørge" });

		int dutchCount = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsDutch);
		int swedishCount = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsSwedish);
		if (danishCount < 2 && dutchCount < count && swedishCount < count)
		{
			return "no";
		}
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsSwedish);
	if (count > bestCount)
	{
		return "sv";
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsSpanish);
	if (count > bestCount)
	{
		std::vector<std::string> word_vec;


		int frenchCount = LanguageAutoDetect::GetCount(text, word_vec = { "[Cc]'est", "pas", "vous", "pour", "suis", "Pourquoi", "maison", "souviens", "quelque" }); // not spanish words

		int portugueseCount = LanguageAutoDetect::GetCount(text, word_vec = { "[NnCc]ão", "Então", "h?ouve", "pessoal", "rapariga", "tivesse", "fizeste", "jantar", "conheço", "atenção", "foste", "milhões", "devias", "ganhar", "raios" }); // not spanish words
		if (frenchCount < 2 && portugueseCount < 2)
		{
			return "es";
		}
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsItalian);
	if (count > bestCount)
	{
		std::vector<std::string> word_vec;

		int frenchCount = LanguageAutoDetect::GetCount(text, word_vec = { "[Cc]'est", "pas", "vous", "pour", "suis", "Pourquoi", "maison", "souviens", "quelque" }); // not italian words
		if (frenchCount < 2)
		{
			return "it";
		}
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsFrench);
	if (count > bestCount)
	{
		std::vector<std::string> word_vec;

		int romanianCount = LanguageAutoDetect::GetCount(text, word_vec = { "[Vv]reau", "[Ss]înt", "[Aa]cum", "pentru", "domnule", "aici" });

		if (romanianCount < 5)
		{
			return "fr";
		}
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsPortuguese);
	if (count > bestCount)
	{
		return "pt"; // Portuguese
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsGerman);
	if (count > bestCount)
	{
		return "de";
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsDutch);
	if (count > bestCount)
	{
		return "nl";
	}

	return "";
}


std::string LanguageAutoDetect::AutoDetectGoogleLanguage2(const std::string& text, int bestCount)
{
	int count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsPolish);
	if (count > bestCount)
	{
		return "pl";
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsGreek);
	if (count > bestCount)
	{
		return "el"; // Greek
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsRussian);
	if (count > bestCount)
	{
		auto bulgarianCount = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsBulgarian);
		if (bulgarianCount > count)
		{
			return "bg"; // Bulgarian
		}

		auto ukranianCount = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsUkrainian);
		if (ukranianCount > count)
		{
			return "uk"; // Ukrainian
		}

		return "ru"; // Russian
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsUkrainian);
	if (count > bestCount)
	{
		return "uk"; // Ukrainian
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsBulgarian);
	if (count > bestCount)
	{
		return "bg"; // Bulgarian
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsAlbanian);
	if (count > bestCount)
	{
		return "sq"; // Albanian
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsArabic);
	if (count > bestCount)
	{
		int hebrewCount = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsHebrew);
		int farsiCount = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsFarsi);
		if (hebrewCount < count && farsiCount < count)
		{
			return "ar"; // Arabic
		}
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsHebrew);
	if (count > bestCount)
	{
		return "he"; // Hebrew
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsFarsi);
	if (count > bestCount)
	{
		return "fa"; // Farsi (Persian)
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsCroatianAndSerbian);
	if (count > bestCount)
	{
		int croatianCount = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsCroatian);
		int serbianCount = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsSerbian);
		if (croatianCount > serbianCount)
		{
			return "hr"; // Croatian
		}

		return "sr"; // Serbian
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsVietnamese);
	if (count > bestCount)
	{
		return "vi"; // Vietnamese
	}

	return "";
}


std::string LanguageAutoDetect::AutoDetectGoogleLanguage3(const std::string& text, int bestCount)
{
	int count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsHungarian);
	if (count > bestCount)
	{
		return "hu"; // Hungarian
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsTurkish);
	if (count > bestCount)
	{
		return "tr"; // Turkish
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsIndonesian);
	if (count > bestCount)
	{
		return "id"; // Indonesian
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsThai);
	if (count > 10 || count > bestCount)
	{
		return "th"; // Thai
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsKorean);
	if (count > 10 || count > bestCount)
	{
		return "ko"; // Korean
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsFinnish);
	if (count > bestCount)
	{
		return "fi"; // Finnish
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsRomanian);
	if (count > bestCount)
	{
		return "ro"; // Romanian
	}

	std::vector<std::string> word_vec;

	count = LanguageAutoDetect::GetCountContains(text, word_vec = { "シ", "ュ", "シン", "シ", "ン", "ユ" });

	count += LanguageAutoDetect::GetCountContains(text, word_vec = { "イ", "ン", "チ", "ェ", "ク", "ハ" });

	count += LanguageAutoDetect::GetCountContains(text, word_vec = { "シ", "ュ", "う", "シ", "ン", "サ" });

	count += LanguageAutoDetect::GetCountContains(text, word_vec = { "シ", "ュ", "シ", "ン", "だ", "う" });

	if (count > bestCount * 2)
	{
		return "ja"; // Japanese - not tested...
	}

	count = LanguageAutoDetect::GetCountContains(text, word_vec = { "是", "是早", "吧", "的", "爱", "上好" });

	count += LanguageAutoDetect::GetCountContains(text, word_vec = { "的", "啊", "好", "好", "亲", "的" });

	count += LanguageAutoDetect::GetCountContains(text, word_vec = { "谢", "走", "吧", "晚", "上", "好" });

	count += LanguageAutoDetect::GetCountContains(text, word_vec = { "来", "卡", "拉", "吐", "滚", "他" });

	if (count > bestCount * 2)
	{
		return "zh"; // Chinese (simplified) - not tested...
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsCzechAndSlovak);
	if (count > bestCount)
	{
		auto lithuanianCount = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsLithuanian);
		int finnishCount = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsFinnish);
		if (lithuanianCount <= count && finnishCount < count)
		{
			int czechWordsCount = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsCzech);
			int slovakWordsCount = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsSlovak);
			if (czechWordsCount >= slovakWordsCount)
			{
				return "cs"; // Czech
			}

			return "sk"; // Slovak
		}
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsLatvian);
	if (count > bestCount * 1.2)
	{
		return "lv";
	}

	count = LanguageAutoDetect::GetCount(text, LanguageAutoDetect::AutoDetectWordsLithuanian);
	if (count > bestCount)
	{
		return "lt";
	}

	return "";
}


std::string LanguageAutoDetect::GetEncodingViaLetterD(const std::string& text)
{
	auto dictionary = std::unordered_map<std::string, int>();

	// Arabic
	int count = 0;
	for (auto letter : "غظضذخثتشرقصفعسنملكيطحزوهدجبا")
	{
		if (StringExtensions::Contains(text, letter))
		{
			count++;
		}
	}
	dictionary.emplace("ar", count);

	// Korean
	count = 0;
	for (auto letter : "가나다라마바사아자차카타파하아야어여오요우유으이")
	{
		if (StringExtensions::Contains(text, letter))
		{
			count++;
		}
	}
	dictionary.emplace("ko", count);

	// Japanese
	count = 0;
	for (auto letter : "あいうえおかきくけこがぎぐげごさしすせそざじずぜぞたちつてとだぢづでどなにぬねのはひふへほばびぶべぼぱぴぷぺぽまみむめもやゆよらりるれろわをん")
	{
		if (StringExtensions::Contains(text, letter))
		{
			count++;
		}
	}
	dictionary.emplace("ja", count);

	// Thai
	count = 0;
	for (auto letter : "กขฃคฅฆงจฉชซฌญฎฏฐฑฒณดตถทธนบปผฝพฟภมยรลวศษสหฬอฮ")
	{
		if (StringExtensions::Contains(text, letter))
		{
			count++;
		}
	}
	dictionary.emplace("th", count);

	// Sinhalese
	count = 0;
	for (auto letter : "අආඇඈඉඊඋඌඍඎඏඐඑඒඓඔඕඖකඛගඝඞඟචඡජඣඤඥඦටඨඩඪණඬතථදධනඳපඵබභමඹයරලවශෂසහළෆ්ාැෑිීුූෘෙේෛොෝෞෟ෦෧෨෩෪෫෬෭෮෯")
	{
		if (StringExtensions::Contains(text, letter))
		{
			count++;
		}
	}
	dictionary.emplace("sl", count);

	// Urdu
	count = 0;
	for (auto letter : "ﺍﺎﺁﺂﺏﺑﺒﺐﭖﭘﭙﭗﺕﺗﺘﺖﭦﭨﭩﭧﺙﺛﺜﺚﺝﺟﺠﺞﭺﭼﭽﭻﺡﺣﺤﺢﺥﺧﺨﺦﺩﺪﺫﺬﺭﺮﮌﮍﺯﺰﮊﮋﺱﺳﺴﺲﺵﺷﺸﺶﺹﺻﺼﺺﺽﺿﻀﺾﻁﻃﻄﻂﻅﻇﻈﻆﻉﻋﻌﻊﻍﻏﻐﻎﻑﻓﻔﻒﻕﻗﻘﻖﻙﻛﻜﻚﻻﻼﻝﻟﻠﻞﻡﻣﻤﻢﻥﻧﻨﻦﻭﻮﮮﮯﮦﮨﮩﮧﯼﯾﯿﯽﮪﮬﮭﮫﴽﴼﺀﺋﺌﹱﹷﹹ")
	{
		if (StringExtensions::Contains(text, letter))
		{
			count++;
		}
	}
	dictionary.emplace("ur", count);

	/*	auto maxHitsLanguage = dictionary.FirstOrDefault([&] (std::any x)
		{
			return x->Value == dictionary.Values->Max();
		});
		return maxHitsLanguage->Value > 0 ? maxHitsLanguage->Key : "";*/

	int max_count = 0/*, max_index = 0*/;
	std::string max_lang = "";
	std::unordered_map<std::string, int>::iterator iterator;
	iterator = dictionary.begin();
	for (int i = 0; i < (int) dictionary.size(); i++)
	{
		if (max_count < iterator->second)
		{
			max_lang = iterator->first;
			max_count = iterator->second;
		}
		iterator++;
	}
	return max_lang;
}
