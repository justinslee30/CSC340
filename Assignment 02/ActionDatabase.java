package javaDictionary;

public enum ActionDatabase {
    NOUN("noun"),
    ADJECTIVE("adjective"),
    ADVERB("adverb"),
    VERB("verb"),
    CONJUNCTION("conjunction"),
    INTERJECTION("interjection"),
    PREPOSITION("preposition"),
    DISTINCT("distinct"),
    REVERSE("reverse"),
    HELP("!help"),
    QUIT("!q");

    private final String cName;

    ActionDatabase(String cName) {
        this.cName = cName;
    }

    public String getcName() {
        return cName;
    }
}
