#define SCREEN_CELLS (2000)
#define ROW_CELLS (80)
#define ROW_COUNT (25)
#define PLAIN (0x0700)
#define BLANK (PLAIN | ' ')
#define LIMIT (40)
#define ALPHABET (26)
#define GATE_FLAGS (0x8E)
#define CODE_SEL (0x08)
#define PIC_CMD (0x20)
#define PIC_MASK (0x21)
#define KBD_DATA (0x60)
#define KBD_STATE (0x64)
#define CRT_INDEX (0x3D4)
#define CLOCK_INDEX (0x70)
#define CLOCK_DATA (0x71)
#define POWER_PORT (0x604)

extern "C" int kmain();
extern "C" void kbd_service();

static unsigned short* const g_grid = (unsigned short*)0xb8000;
static volatile unsigned char* const g_flags = (volatile unsigned char*)0x9000;

struct dict_pair
{
    const char* en;
    const char* fi;
};

#define DICT_SIZE 508

static const struct dict_pair g_dict[DICT_SIZE] = {
    {"able", "kykeneva"},
    {"above", "yll" "\x84"},
    {"accident", "onnettomuus"},
    {"actor", "n" "\x84" "yttelij" "\x84"},
    {"address", "osoite"},
    {"advice", "neuvo"},
    {"afternoon", "iltap" "\x84" "iv" "\x84"},
    {"against", "vastaan"},
    {"age", "ik" "\x84"},
    {"agreement", "sopimus"},
    {"air", "ilma"},
    {"airport", "lentokentt" "\x84"},
    {"alone", "yksin"},
    {"always", "aina"},
    {"anchor", "ankkuri"},
    {"angel", "enkeli"},
    {"anger", "viha"},
    {"angry", "vihainen"},
    {"animal", "el" "\x84" "in"},
    {"answer", "vastaus"},
    {"ant", "muurahainen"},
    {"apartment", "asunto"},
    {"apple", "omena"},
    {"arm", "k" "\x84" "sivarsi"},
    {"aunt", "t" "\x84" "ti"},
    {"baby", "vauva"},
    {"back", "selk" "\x84"},
    {"bad", "huono"},
    {"bag", "laukku"},
    {"ball", "pallo"},
    {"banana", "banaani"},
    {"bank", "pankki"},
    {"bath", "kylpy"},
    {"beach", "ranta"},
    {"bean", "papu"},
    {"bear", "karhu"},
    {"beard", "parta"},
    {"beautiful", "kaunis"},
    {"because", "koska"},
    {"bed", "s" "\x84" "nky"},
    {"bee", "mehil" "\x84" "inen"},
    {"beer", "olut"},
    {"before", "ennen"},
    {"belt", "vy" "\x94"},
    {"between", "v" "\x84" "liss" "\x84"},
    {"bicycle", "polkupy" "\x94" "r" "\x84"},
    {"birthday", "syntym" "\x84" "p" "\x84" "iv" "\x84"},
    {"bitter", "kitker" "\x84"},
    {"bread", "leip" "\x84"},
    {"bucket", "\x84" "mp" "\x84" "ri"},
    {"cabbage", "kaali"},
    {"cake", "kakku"},
    {"calm", "tyyni"},
    {"camera", "kamera"},
    {"candle", "kynttil" "\x84"},
    {"captain", "kapteeni"},
    {"car", "auto"},
    {"careful", "varovainen"},
    {"carpet", "matto"},
    {"carrot", "porkkana"},
    {"castle", "linna"},
    {"cat", "kissa"},
    {"cellar", "kellari"},
    {"century", "vuosisata"},
    {"chain", "ketju"},
    {"chair", "tuoli"},
    {"chalk", "liitu"},
    {"cheap", "halpa"},
    {"cheek", "poski"},
    {"cheese", "juusto"},
    {"circle", "ympyr" "\x84"},
    {"cold", "kylm" "\x84"},
    {"color", "v" "\x84" "ri"},
    {"cough", "ysk" "\x84"},
    {"cow", "lehm" "\x84"},
    {"daily", "p" "\x84" "ivitt" "\x84" "inen"},
    {"dance", "tanssi"},
    {"danger", "vaara"},
    {"dark", "pime" "\x84"},
    {"daughter", "tyt" "\x84" "r"},
    {"day", "p" "\x84" "iv" "\x84"},
    {"deaf", "kuuro"},
    {"death", "kuolema"},
    {"debt", "velka"},
    {"decision", "p" "\x84" "\x84" "t" "\x94" "s"},
    {"deep", "syv" "\x84"},
    {"deer", "peura"},
    {"desert", "aavikko"},
    {"diamond", "timantti"},
    {"dictionary", "sanakirja"},
    {"difficult", "vaikea"},
    {"dinner", "illallinen"},
    {"dirty", "likainen"},
    {"doctor", "l" "\x84" "\x84" "k" "\x84" "ri"},
    {"dog", "koira"},
    {"door", "ovi"},
    {"dove", "kyyhkynen"},
    {"dozen", "tusina"},
    {"dream", "uni"},
    {"dust", "p" "\x94" "ly"},
    {"eagle", "kotka"},
    {"ear", "korva"},
    {"early", "aikainen"},
    {"earth", "maa"},
    {"east", "it" "\x84"},
    {"easy", "helppo"},
    {"economy", "talous"},
    {"edge", "reuna"},
    {"education", "koulutus"},
    {"egg", "muna"},
    {"eight", "kahdeksan"},
    {"elbow", "kyyn" "\x84" "rp" "\x84" "\x84"},
    {"elephant", "norsu"},
    {"eleven", "yksitoista"},
    {"empty", "tyhj" "\x84"},
    {"end", "loppu"},
    {"enemy", "vihollinen"},
    {"engine", "moottori"},
    {"engineer", "insin" "\x94" "\x94" "ri"},
    {"envelope", "kirjekuori"},
    {"equal", "tasa-arvoinen"},
    {"error", "virhe"},
    {"evening", "ilta"},
    {"exam", "koe"},
    {"eye", "silm" "\x84"},
    {"face", "kasvot"},
    {"factory", "tehdas"},
    {"fair", "reilu"},
    {"family", "perhe"},
    {"farm", "maatila"},
    {"fast", "nopea"},
    {"fat", "lihava"},
    {"father", "is" "\x84"},
    {"fault", "vika"},
    {"fear", "pelko"},
    {"feather", "sulka"},
    {"fence", "aita"},
    {"fever", "kuume"},
    {"field", "pelto"},
    {"fifty", "viisikymment" "\x84"},
    {"fight", "taistelu"},
    {"finger", "sormi"},
    {"first", "ensimm" "\x84" "inen"},
    {"fly", "k" "\x84" "rp" "\x84" "nen"},
    {"forest", "mets" "\x84"},
    {"forty", "nelj" "\x84" "kymment" "\x84"},
    {"four", "nelj" "\x84"},
    {"friend", "yst" "\x84" "v" "\x84"},
    {"fruit", "hedelm" "\x84"},
    {"full", "t" "\x84" "ysi"},
    {"game", "peli"},
    {"garden", "puutarha"},
    {"garlic", "valkosipuli"},
    {"gasoline", "bensiini"},
    {"gate", "portti"},
    {"gift", "lahja"},
    {"girl", "tytt" "\x94"},
    {"glass", "lasi"},
    {"glove", "hansikas"},
    {"glue", "liima"},
    {"goat", "vuohi"},
    {"gold", "kulta"},
    {"good", "hyv" "\x84"},
    {"goose", "hanhi"},
    {"government", "hallitus"},
    {"grain", "vilja"},
    {"grandfather", "isois" "\x84"},
    {"grandmother", "isot" "\x84" "ti"},
    {"grape", "viiniryp" "\x84" "le"},
    {"grass", "ruoho"},
    {"gray", "harmaa"},
    {"green", "vihre" "\x84"},
    {"ground", "maa"},
    {"group", "ryhm" "\x84"},
    {"growth", "kasvu"},
    {"habit", "tapa"},
    {"hair", "hiukset"},
    {"half", "puoli"},
    {"hall", "sali"},
    {"hammer", "vasara"},
    {"hand", "k" "\x84" "si"},
    {"handle", "kahva"},
    {"happy", "onnellinen"},
    {"harbor", "satama"},
    {"hard", "kova"},
    {"hare", "j" "\x84" "nis"},
    {"harvest", "sato"},
    {"hat", "hattu"},
    {"hay", "hein" "\x84"},
    {"haystack", "hein" "\x84" "suova"},
    {"head", "p" "\x84" "\x84"},
    {"health", "terveys"},
    {"heart", "syd" "\x84" "n"},
    {"heel", "kantap" "\x84" "\x84"},
    {"hill", "m" "\x84" "ki"},
    {"hole", "reik" "\x84"},
    {"holy", "pyh" "\x84"},
    {"hunger", "n" "\x84" "lk" "\x84"},
    {"hunter", "mets" "\x84" "st" "\x84" "j" "\x84"},
    {"hut", "m" "\x94" "kki"},
    {"ice", "j" "\x84" "\x84"},
    {"idea", "idea"},
    {"ill", "sairas"},
    {"important", "t" "\x84" "rke" "\x84"},
    {"impossible", "mahdoton"},
    {"innocent", "viaton"},
    {"insect", "hy" "\x94" "nteinen"},
    {"inside", "sis" "\x84" "ll" "\x84"},
    {"invitation", "kutsu"},
    {"iron", "rauta"},
    {"island", "saari"},
    {"jacket", "takki"},
    {"jam", "hillo"},
    {"jaw", "leuka"},
    {"jealous", "mustasukkainen"},
    {"jewel", "jalokivi"},
    {"job", "ty" "\x94"},
    {"joke", "vitsi"},
    {"journey", "matka"},
    {"joy", "ilo"},
    {"judge", "tuomari"},
    {"juice", "mehu"},
    {"jump", "hyppy"},
    {"juniper", "kataja"},
    {"justice", "oikeus"},
    {"kettle", "pannu"},
    {"key", "avain"},
    {"kidney", "munuainen"},
    {"kind", "kiltti"},
    {"king", "kuningas"},
    {"kiss", "suudelma"},
    {"kitchen", "keitti" "\x94"},
    {"kite", "leija"},
    {"kitten", "kissanpentu"},
    {"knee", "polvi"},
    {"knife", "veitsi"},
    {"knot", "solmu"},
    {"knowledge", "tieto"},
    {"ladder", "tikkaat"},
    {"lake", "j" "\x84" "rvi"},
    {"lamb", "karitsa"},
    {"lamp", "lamppu"},
    {"language", "kieli"},
    {"lantern", "lyhty"},
    {"last", "viimeinen"},
    {"late", "my" "\x94" "h" "\x84" "inen"},
    {"law", "laki"},
    {"lazy", "laiska"},
    {"leaf", "lehti"},
    {"leather", "nahka"},
    {"left", "vasen"},
    {"leg", "jalka"},
    {"lemon", "sitruuna"},
    {"lesson", "oppitunti"},
    {"letter", "kirje"},
    {"level", "taso"},
    {"library", "kirjasto"},
    {"lie", "valhe"},
    {"life", "el" "\x84" "m" "\x84"},
    {"light", "valo"},
    {"lightning", "salama"},
    {"lily", "lilja"},
    {"long", "pitk" "\x84"},
    {"machine", "kone"},
    {"mad", "hullu"},
    {"magazine", "lehti"},
    {"magic", "taikuus"},
    {"mail", "posti"},
    {"main", "p" "\x84" "\x84"},
    {"man", "mies"},
    {"manner", "tapa"},
    {"map", "kartta"},
    {"market", "tori"},
    {"marriage", "avioliitto"},
    {"marsh", "suo"},
    {"mast", "masto"},
    {"match", "tulitikku"},
    {"mean", "ilke" "\x84"},
    {"meaning", "merkitys"},
    {"meat", "liha"},
    {"medicine", "l" "\x84" "\x84" "ke"},
    {"memory", "muisti"},
    {"message", "viesti"},
    {"metal", "metalli"},
    {"middle", "keskikohta"},
    {"midnight", "keskiy" "\x94"},
    {"mild", "mieto"},
    {"mother", "\x84" "iti"},
    {"nail", "naula"},
    {"naked", "alaston"},
    {"name", "nimi"},
    {"narrow", "kapea"},
    {"nation", "kansakunta"},
    {"nature", "luonto"},
    {"necessary", "tarpeellinen"},
    {"neck", "kaula"},
    {"needle", "neula"},
    {"neighbor", "naapuri"},
    {"nest", "pes" "\x84"},
    {"net", "verkko"},
    {"nettle", "nokkonen"},
    {"never", "ei koskaan"},
    {"new", "uusi"},
    {"news", "uutiset"},
    {"newspaper", "sanomalehti"},
    {"night", "y" "\x94"},
    {"nine", "yhdeks" "\x84" "n"},
    {"noble", "jalo"},
    {"noise", "melu"},
    {"noon", "keskip" "\x84" "iv" "\x84"},
    {"nose", "nen" "\x84"},
    {"nothing", "ei mit" "\x84" "\x84" "n"},
    {"nut", "p" "\x84" "hkin" "\x84"},
    {"oak", "tammi"},
    {"oat", "kaura"},
    {"obedient", "tottelevainen"},
    {"object", "esine"},
    {"ocean", "valtameri"},
    {"offer", "tarjous"},
    {"office", "toimisto"},
    {"often", "usein"},
    {"oil", "\x94" "ljy"},
    {"old", "vanha"},
    {"one", "yksi"},
    {"onion", "sipuli"},
    {"open", "avoin"},
    {"opinion", "mielipide"},
    {"opposite", "vastakohta"},
    {"orange", "appelsiini"},
    {"order", "j" "\x84" "rjestys"},
    {"outside", "ulkona"},
    {"oven", "uuni"},
    {"owl", "p" "\x94" "ll" "\x94"},
    {"owner", "omistaja"},
    {"ox", "h" "\x84" "rk" "\x84"},
    {"pack", "pakkaus"},
    {"page", "sivu"},
    {"pail", "sanko"},
    {"pain", "kipu"},
    {"pair", "pari"},
    {"palace", "palatsi"},
    {"pale", "kalpea"},
    {"pan", "pannu"},
    {"paper", "paperi"},
    {"parents", "vanhemmat"},
    {"park", "puisto"},
    {"part", "osa"},
    {"partridge", "peltopyy"},
    {"past", "menneisyys"},
    {"path", "polku"},
    {"patience", "k" "\x84" "rsiv" "\x84" "llisyys"},
    {"payment", "maksu"},
    {"pear", "p" "\x84" "\x84" "ryn" "\x84"},
    {"pen", "kyn" "\x84"},
    {"person", "henkil" "\x94"},
    {"pilot", "lent" "\x84" "j" "\x84"},
    {"pine", "m" "\x84" "nty"},
    {"pity", "s" "\x84" "\x84" "li"},
    {"poor", "k" "\x94" "yh" "\x84"},
    {"proud", "ylpe" "\x84"},
    {"quality", "laatu"},
    {"quantity", "m" "\x84" "\x84" "r" "\x84"},
    {"quarrel", "riita"},
    {"quarter", "nelj" "\x84" "nnes"},
    {"queen", "kuningatar"},
    {"question", "kysymys"},
    {"quick", "nopea"},
    {"quiet", "hiljainen"},
    {"quilt", "peitto"},
    {"rabbit", "kani"},
    {"railway", "rautatie"},
    {"rain", "sade"},
    {"rainbow", "sateenkaari"},
    {"raspberry", "vadelma"},
    {"rat", "rotta"},
    {"raven", "korppi"},
    {"raw", "raaka"},
    {"ready", "valmis"},
    {"reason", "syy"},
    {"red", "punainen"},
    {"reindeer", "poro"},
    {"rescue", "pelastus"},
    {"respect", "kunnioitus"},
    {"rest", "lepo"},
    {"result", "tulos"},
    {"reward", "palkkio"},
    {"ribbon", "nauha"},
    {"rice", "riisi"},
    {"rich", "rikas"},
    {"ripe", "kyps" "\x84"},
    {"rope", "k" "\x94" "ysi"},
    {"round", "py" "\x94" "re" "\x84"},
    {"rude", "t" "\x94" "yke" "\x84"},
    {"rule", "s" "\x84" "\x84" "nt" "\x94"},
    {"sack", "s" "\x84" "kki"},
    {"sample", "n" "\x84" "yte"},
    {"scared", "pel" "\x84" "stynyt"},
    {"search", "etsint" "\x84"},
    {"seven", "seitsem" "\x84" "n"},
    {"shame", "h" "\x84" "pe" "\x84"},
    {"sharp", "ter" "\x84" "v" "\x84"},
    {"shoe", "kenk" "\x84"},
    {"shoulder", "olkap" "\x84" "\x84"},
    {"sight", "n" "\x84" "k" "\x94"},
    {"single", "yksitt" "\x84" "inen"},
    {"smooth", "sile" "\x84"},
    {"snake", "k" "\x84" "\x84" "rme"},
    {"soft", "pehme" "\x84"},
    {"soil", "maaper" "\x84"},
    {"sound", "\x84" "\x84" "ni"},
    {"south", "etel" "\x84"},
    {"spider", "h" "\x84" "m" "\x84" "h" "\x84" "kki"},
    {"spot", "t" "\x84" "pl" "\x84"},
    {"spring", "kev" "\x84" "t"},
    {"star", "t" "\x84" "hti"},
    {"steam", "h" "\x94" "yry"},
    {"steel", "ter" "\x84" "s"},
    {"steep", "jyrkk" "\x84"},
    {"stiff", "j" "\x84" "ykk" "\x84"},
    {"table", "p" "\x94" "yt" "\x84"},
    {"tail", "h" "\x84" "nt" "\x84"},
    {"tall", "pitk" "\x84"},
    {"taste", "maku"},
    {"tax", "vero"},
    {"tea", "tee"},
    {"teacher", "opettaja"},
    {"tear", "kyynel"},
    {"ten", "kymmenen"},
    {"tender", "hell" "\x84"},
    {"tent", "teltta"},
    {"test", "koe"},
    {"thank", "kiitos"},
    {"theater", "teatteri"},
    {"thick", "paksu"},
    {"thief", "varas"},
    {"thin", "laiha"},
    {"thirst", "jano"},
    {"thirty", "kolmekymment" "\x84"},
    {"thousand", "tuhat"},
    {"tired", "v" "\x84" "synyt"},
    {"today", "t" "\x84" "n" "\x84" "\x84" "n"},
    {"tool", "ty" "\x94" "kalu"},
    {"turn", "k" "\x84" "\x84" "nn" "\x94" "s"},
    {"twenty", "kaksikymment" "\x84"},
    {"ugly", "ruma"},
    {"umbrella", "sateenvarjo"},
    {"uncle", "set" "\x84"},
    {"under", "alla"},
    {"university", "yliopisto"},
    {"useful", "hy" "\x94" "dyllinen"},
    {"useless", "hy" "\x94" "dyt" "\x94" "n"},
    {"usual", "tavallinen"},
    {"valley", "laakso"},
    {"value", "arvo"},
    {"vegetable", "vihannes"},
    {"vein", "suoni"},
    {"verse", "s" "\x84" "e"},
    {"vessel", "astia"},
    {"victory", "voitto"},
    {"view", "n" "\x84" "kym" "\x84"},
    {"village", "kyl" "\x84"},
    {"violin", "viulu"},
    {"visit", "vierailu"},
    {"visitor", "vierailija"},
    {"voice", "\x84" "\x84" "ni"},
    {"wage", "palkka"},
    {"wagon", "vaunu"},
    {"waist", "vy" "\x94" "t" "\x84" "r" "\x94"},
    {"walk", "k" "\x84" "vely"},
    {"wall", "sein" "\x84"},
    {"war", "sota"},
    {"warm", "l" "\x84" "mmin"},
    {"warning", "varoitus"},
    {"wasp", "ampiainen"},
    {"waste", "tuhlaus"},
    {"watch", "kello"},
    {"water", "vesi"},
    {"wave", "aalto"},
    {"wax", "vaha"},
    {"weak", "heikko"},
    {"weather", "s" "\x84" "\x84"},
    {"wedding", "h" "\x84" "\x84" "t"},
    {"west", "l" "\x84" "nsi"},
    {"wet", "m" "\x84" "rk" "\x84"},
    {"wheat", "vehn" "\x84"},
    {"wheel", "py" "\x94" "r" "\x84"},
    {"wide", "leve" "\x84"},
    {"work", "ty" "\x94"},
    {"worker", "ty" "\x94" "ntekij" "\x84"},
    {"wrong", "v" "\x84" "\x84" "r" "\x84"},
    {"xylophone", "ksylofoni"},
    {"yard", "piha"},
    {"yarn", "lanka"},
    {"yawn", "haukotus"},
    {"year", "vuosi"},
    {"yellow", "keltainen"},
    {"yes", "kyll" "\x84"},
    {"yesterday", "eilen"},
    {"yolk", "keltuainen"},
    {"young", "nuori"},
    {"youth", "nuoruus"},
    {"zeal", "into"},
    {"zebra", "seepra"},
    {"zero", "nolla"},
    {"zinc", "sinkki"},
    {"zipper", "vetoketju"},
    {"zone", "vy" "\x94" "hyke"},
    {"zoo", "el" "\x84" "intarha"}
};

static unsigned char pin(unsigned short port)
{
    unsigned char got;
    __asm {
        mov dx, port
        in al, dx
        mov got, al
    }
    return got;
}

static void pout(unsigned short port, unsigned char value)
{
    __asm {
        mov dx, port
        mov al, value
        out dx, al
    }
}

static void pout16(unsigned short port, unsigned short value)
{
    __asm {
        mov dx, port
        mov ax, value
        out dx, ax
    }
}

#pragma pack(push, 1)
struct gate
{
    unsigned short low;
    unsigned short sel;
    unsigned char pad;
    unsigned char kind;
    unsigned short high;
};

struct table_ref
{
    unsigned short bound;
    unsigned int origin;
};
#pragma pack(pop)

static struct gate g_vectors[256];
static struct table_ref g_vectors_ref;

__declspec(naked) static void ignore_irq()
{
    __asm {
        iretd
    }
}

static void bind_vector(int number, void (*routine)())
{
    unsigned int where = (unsigned int)routine;
    g_vectors[number].low = (unsigned short)where;
    g_vectors[number].high = (unsigned short)(where >> 16);
    g_vectors[number].sel = CODE_SEL;
    g_vectors[number].pad = 0;
    g_vectors[number].kind = GATE_FLAGS;
}

static void arm_vectors()
{
    int i;
    for (i = 0; i < 256; i++)
        bind_vector(i, ignore_irq);
    g_vectors_ref.origin = (unsigned int)g_vectors;
    g_vectors_ref.bound = sizeof(g_vectors) - 1;
    __asm {
        lidt g_vectors_ref
    }
}

static unsigned short* g_spot;

static void sync_caret()
{
    unsigned short offset = (unsigned short)(g_spot - g_grid);
    pout(CRT_INDEX, 0x0F);
    pout(CRT_INDEX + 1, (unsigned char)offset);
    pout(CRT_INDEX, 0x0E);
    pout(CRT_INDEX + 1, (unsigned char)(offset >> 8));
}

static void wipe()
{
    int i;
    for (i = 0; i < SCREEN_CELLS; i++)
        g_grid[i] = BLANK;
    g_spot = g_grid;
    sync_caret();
}

static void roll_up()
{
    int i;
    for (i = 0; i < SCREEN_CELLS - ROW_CELLS; i++)
        g_grid[i] = g_grid[i + ROW_CELLS];
    for (i = SCREEN_CELLS - ROW_CELLS; i < SCREEN_CELLS; i++)
        g_grid[i] = BLANK;
}

static void wrap_if_needed()
{
    if (g_spot < g_grid + SCREEN_CELLS)
        return;
    roll_up();
    g_spot = g_grid + SCREEN_CELLS - ROW_CELLS;
}

static void step_line()
{
    unsigned int passed = (unsigned int)(g_spot - g_grid);
    g_spot += ROW_CELLS - (passed % ROW_CELLS);
    wrap_if_needed();
    sync_caret();
}

static void emit(char sign)
{
    if (sign == '\n')
    {
        step_line();
        return;
    }
    *g_spot++ = (unsigned short)(PLAIN | (unsigned char)sign);
    wrap_if_needed();
    sync_caret();
}

static void say(const char* text)
{
    while (*text)
        emit(*text++);
}

static void say_number(unsigned value)
{
    if (value >= 10)
        say_number(value / 10);
    emit((char)('0' + value % 10));
}

static void undo_char()
{
    g_spot--;
    *g_spot = BLANK;
    sync_caret();
}

static char g_typed[LIMIT + 1];
static char* g_tail;

static unsigned typed_length()
{
    return (unsigned)(g_tail - g_typed);
}

static void reset_typed()
{
    g_tail = g_typed;
    g_typed[0] = 0;
}

static int lowercase(char sign)
{
    return sign >= 'a' && sign <= 'z';
}

static int relate(const char* left, const char* right)
{
    while (*left && *left == *right)
    {
        left++;
        right++;
    }
    return (int)(unsigned char)*left - (int)(unsigned char)*right;
}

static unsigned g_noise;

static unsigned shake() //лкг
{
    g_noise = g_noise * 1103515245u + 12345u;
    return (g_noise >> 16) & 0x7FFF;
}

static unsigned g_per_letter[ALPHABET];

static void survey_dictionary()
{
    int i;
    for (i = 0; i < ALPHABET; i++)
        g_per_letter[i] = 0;
    for (i = 0; i < DICT_SIZE; i++)
        g_per_letter[g_dict[i].en[0] - 'a']++;
}

static int allowed_letter(char sign)
{
    return lowercase(sign) && g_flags[sign - 'a'] != 0;
}

static unsigned available_count(char sign)
{
    return allowed_letter(sign) ? g_per_letter[sign - 'a'] : 0;
}

static unsigned available_total()
{
    unsigned sum = 0;
    int i;
    for (i = 0; i < ALPHABET; i++)
        if (g_flags[i])
            sum += g_per_letter[i];
    return sum;
}
//бин поиск для слов
static const struct dict_pair* seek(const char* word)
{
    unsigned base = 0;
    unsigned span = DICT_SIZE;
    while (span)
    {
        unsigned half = span / 2;
        const struct dict_pair* probe = &g_dict[base + half];
        int rel = relate(word, probe->en);
        if (rel == 0)
            return probe;
        if (rel > 0)
        {
            base += half + 1;
            span -= half + 1;
        }
        else
            span = half;
    }
    return 0;
}

static void blame_word(const char* word, const char* cause)
{
    say("Error: A word '");
    say(word);
    say("' is ");
    say(cause);
    emit('\n');
}

static void show_info(const char* unused)
{
    char sign;
    say("DictOS (en to fi). Author: Andreeva Maria, gr 5151003/40001, SPbPU\n");
    say("Compilers: bootloader: yasm (AT&T syntax), kernel: Microsoft C compiler\n");
    say("Bootloader parameters: enabled letters: ");
    for (sign = 'a'; sign <= 'z'; sign++)
        if (allowed_letter(sign))
            emit(sign);
    emit('\n');
}

static void show_dictinfo(const char* unused)
{
    say("Dictionary: en to fi\n");
    say("Number of words: ");
    say_number(DICT_SIZE);
    emit('\n');
    say("Number of loaded words: ");
    say_number(available_total());
    emit('\n');
}

static void show_translation(const char* word)
{
    const char* scan;
    const struct dict_pair* hit;
    if (!word[0])
    {
        say("Error: command incorrect\n");
        return;
    }
    for (scan = word; *scan; scan++)
        if (!lowercase(*scan))
        {
            blame_word(word, "unknown");
            return;
        }
    hit = seek(word);
    if (!hit)
        blame_word(word, "unknown");
    else if (!allowed_letter(word[0]))
        blame_word(word, "not loaded");
    else
    {
        say(hit->fi);
        emit('\n');
    }
}

static void show_wordstat(const char* argument)
{
    unsigned found;
    if (!argument[0] || argument[1] || !lowercase(argument[0]))
    {
        say("Error: command incorrect\n");
        return;
    }
    found = available_count(argument[0]);
    say("Letter '");
    emit(argument[0]);
    say("': ");
    say_number(found);
    say(found == 1 ? " word loaded.\n" : " words loaded.\n");
}

static void show_anyword(const char* argument)
{
    char letter = 0;
    unsigned pool;
    unsigned pick;
    int i;
    if (argument[0])
    {
        if (argument[1] || !lowercase(argument[0]))
        {
            say("Error: command incorrect\n");
            return;
        }
        letter = argument[0];
    }
    pool = letter ? available_count(letter) : available_total();
    if (pool == 0)
    {
        say("Error: no words\n");
        return;
    }
    pick = shake() % pool;
    for (i = 0; i < DICT_SIZE; i++)
    {
        char first = g_dict[i].en[0];
        if (letter && first != letter)
            continue;
        if (!allowed_letter(first))
            continue;
        if (pick-- == 0)
        {
            say(g_dict[i].en);
            say(": ");
            say(g_dict[i].fi);
            emit('\n');
            return;
        }
    }
}

static void power_off(const char* unused)
{
    say("Powering off...\n");
    pout16(POWER_PORT, 0x2000);
    for (;;)
        __asm { hlt }
}

struct verb
{
    const char* word;
    void (*act)(const char*);
    int wants_argument;
};

static const struct verb g_verbs[] = {
    {"info", show_info, 0},
    {"dictinfo", show_dictinfo, 0},
    {"translate", show_translation, 1},
    {"wordstat", show_wordstat, 1},
    {"anyword", show_anyword, 1},
    {"shutdown", power_off, 0}
};

#define VERB_COUNT (sizeof(g_verbs) / sizeof(g_verbs[0]))

static char* skip_blanks(char* p)
{
    while (*p == ' ')
        p++;
    return p;
}

static char* cut_word(char** rest)
{
    char* start = skip_blanks(*rest);
    char* stop = start;
    while (*stop && *stop != ' ')
        stop++;
    if (*stop)
    {
        *stop = 0;
        *rest = stop + 1;
    }
    else
        *rest = stop;
    return start;
}

static void trim_end(char* text)
{
    char* stop = text;
    while (*stop)
        stop++;
    while (stop > text && stop[-1] == ' ')
        stop--;
    *stop = 0;
}

static void obey(char* line)
{
    char* rest = line;
    char* name = cut_word(&rest);
    char* argument = skip_blanks(rest);
    unsigned i;
    trim_end(argument);
    if (!name[0])
        return;
    for (i = 0; i < VERB_COUNT; i++)
    {
        if (relate(name, g_verbs[i].word) != 0)
            continue;
        if (!g_verbs[i].wants_argument && argument[0])
            break;
        g_verbs[i].act(argument);
        return;
    }
    say("Error: command not recognized\n");
}

static const char g_keys[128] = {
      0,   0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',   8,   0,
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',   0,   0,'\n',   0, 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l',   0,   0,   0,   0,   0, 'z', 'x', 'c', 'v',
    'b', 'n', 'm',   0,   0, '/',   0, '*',   0, ' ',   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0, '-',   0,   0,   0, '+',   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};

static int g_upper;

static char with_shift(char sign)
{
    if (lowercase(sign))
        return (char)(sign - 32);
    if (sign == '8')
        return '*';
    if (sign == '=')
        return '+';
    return sign;
}

static int typeable(char sign)
{
    return lowercase(sign)
        || (sign >= 'A' && sign <= 'Z')
        || (sign >= '0' && sign <= '9')
        || sign == ' ' || sign == '+' || sign == '-'
        || sign == '*' || sign == '/';
}

static void prompt()
{
    say("# ");
}

static void take_symbol(char sign)
{
    if (sign == '\n')
    {
        *g_tail = 0;
        step_line();
        obey(g_typed);
        reset_typed();
        prompt();
        return;
    }
    if (sign == 8)
    {
        if (typed_length() == 0)
            return;
        g_tail--;
        undo_char();
        return;
    }
    if (!typeable(sign))
        return;
    if (typed_length() >= LIMIT)
        return;
    *g_tail++ = sign;
    emit(sign);
}

static void take_code(unsigned char code)
{
    char sign;
    if (code == 0x2A || code == 0x36)
    {
        g_upper = 1;
        return;
    }
    if (code == 0xAA || code == 0xB6)
    {
        g_upper = 0;
        return;
    }
    if (code >= 128)
        return;
    sign = g_keys[code];
    if (!sign)
        return;
    if (g_upper)
        sign = with_shift(sign);
    take_symbol(sign);
}

extern "C" void kbd_service()
{
    if (pin(KBD_STATE) & 1)
    {
        unsigned char code = pin(KBD_DATA);
        g_noise = g_noise * 31u + code + 1u;
        take_code(code);
    }
    pout(PIC_CMD, 0x20);
}

__declspec(naked) static void kbd_gate()
{
    __asm {
        pusha
        call kbd_service
        popa
        iretd
    }
}

static unsigned char clock_cell(unsigned char which)
{
    pout(CLOCK_INDEX, which);
    return pin(CLOCK_DATA);
}

extern "C" int kmain()
{
    __asm { cli }

    g_upper = 0;
    reset_typed();

    g_noise = ((unsigned)clock_cell(4) << 16)
        ^ ((unsigned)clock_cell(2) << 8)
        ^ (unsigned)clock_cell(0)
        ^ 0xC0FFEEu;

    survey_dictionary();

    wipe();
    say("Welcome to DictOS (English -> Finnish)!\n");
    prompt();

    arm_vectors();
    bind_vector(0x09, kbd_gate);
    pout(PIC_MASK, 0xFD);

    __asm { sti }

    for (;;)
        __asm { hlt }

    return 0;
}