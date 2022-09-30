package javaDictionary;

import java.util.ArrayList;
import java.util.Arrays;

enum EntryDatabase {
    ARROW(new ArrayList<>(Arrays.asList("noun")),new ArrayList<>(Arrays.asList("Here is one arrow: <IMG> -=>> <\\IMG>"))),
    BOOK(new ArrayList<>(Arrays.asList("noun","noun","verb","verb")),new ArrayList<>(Arrays.asList("A set of pages.", "A " +
                    "written work published in printed or electronic form.","To arrange for someone to have a seat on a plane",
                    "To arrange something on a particular date"))),
    DISTINCT(new ArrayList<>(Arrays.asList("adjective","adjective","adverb","noun","noun","noun","noun","noun")),
            new ArrayList<>(Arrays.asList("Familiar. Worked in Java.","Unique. No duplicates. Clearly different or of a " +
                    "different kind.","Uniquely. Written \"distinctly\".","A keyword in this assignment.","A keyword in this " +
                    "assignment.","A keyword in this assignment.", "An advanced search option", "Distinct is a parameter in this assignment"))),
    PLACEHOLDER(new ArrayList<>(Arrays.asList("adjective","adjective","adverb","conjunction","interjection","noun","nou" +
                    "n","noun","preposition","pronoun","verb")),new ArrayList<>(Arrays.asList("To be updated...","To be " +
                    "updated...","To be updated...","To be updated...","To be updated...","To be updated...","To be upda" +
                    "ted...","To be updated...","To be updated...","To be updated...","To be updated..."))),
    REVERSE(new ArrayList<>(Arrays.asList("adjective","adjective","noun","noun","noun","noun","noun","noun","noun",
                    "verb","verb","verb","verb","verb","verb")),new ArrayList<>(Arrays.asList("On the back side.", "Opposite to" +
                    "usual or previous arrangement","A dictionary program's parameter.","Change to opposite direction.",
                     "The opposite.","To be updated...","To be updated...","To be updated...","To be updated...", "Change " +
                    "something to opposite.", "Go back", "Revoke ruling","To be updated...","To be updated...", "Turn something inside out"))),
    SEASON(new ArrayList<>(Arrays.asList("noun","noun","noun","verb","verb")),new ArrayList<>(Arrays.asList("each of the " +
            "four divisions of the year marked by particular weather patterns and daylight hours", "set or sequence of " +
            "related television programs","a period when a female mammal is ready to mate", "add spices to food", "make wood" +
            " suitable for use as timber by adjusting its moisture content"))),
    ONOMATOPOEIA(new ArrayList<>(Arrays.asList("noun")),new ArrayList<>(Arrays.asList("the formation of a word from a " +
            "sound associated with what is named"))),
    INFORMATICS(new ArrayList<>(Arrays.asList("noun")),new ArrayList<>(Arrays.asList("the science of processing data for storage and retrieval"))),
    DRUG(new ArrayList<>(Arrays.asList("noun","verb")),new ArrayList<>(Arrays.asList("a medicine or other substance which has a " +
            "physiological effect when ingested or otherwise introduced to the body","administer a drug in order to induce stupor"))),
    MARVEL(new ArrayList<>(Arrays.asList("noun","verb")),new ArrayList<>(Arrays.asList("a wonderful or astonishing person or thing",
            "be filled with wonder or astonishment"))),
    CHASE(new ArrayList<>(Arrays.asList("noun","verb","verb")),new ArrayList<>(Arrays.asList("an act of pursuing someone or something",
            "pursue in order to catch or catch up with","drive or cause to go in a certain direction"))),
    VIBE(new ArrayList<>(Arrays.asList("noun")),new ArrayList<>(Arrays.asList("person's emotional state or the atmosphere of a place"))),
    MOOD(new ArrayList<>(Arrays.asList("noun")),new ArrayList<>(Arrays.asList("temporary state of mind or feeling"))),
    EON(new ArrayList<>(Arrays.asList("noun")),new ArrayList<>(Arrays.asList("an indefinite and very long period of time, often a period exaggerated"))),
    BE(new ArrayList<>(Arrays.asList("verb")),new ArrayList<>(Arrays.asList("exist"))),
    CREATE(new ArrayList<>(Arrays.asList("verb")),new ArrayList<>(Arrays.asList("to bring into existence"))),
    POOR(new ArrayList<>(Arrays.asList("adjective")),new ArrayList<>(Arrays.asList("lacking sufficient money to live at a normal standard in a society"))),
    UNFORTUNATE(new ArrayList<>(Arrays.asList("adjective")),new ArrayList<>(Arrays.asList("having or marked by bad fortune; unlucky"))),
    QUITE(new ArrayList<>(Arrays.asList("adverb")),new ArrayList<>(Arrays.asList("absolutely or completely")))
    ;

    //private variables for entry in EntryDatabase
    private ArrayList<String> cPos;
    private ArrayList<String> cDef;

    //constructors

    private EntryDatabase()
    {
        this.cPos = null;
        this.cDef = null;
    }

    private EntryDatabase(ArrayList<String> cPos, ArrayList<String> cDef) {
        this.cPos = cPos;
        this.cDef = cDef;
    }

    public ArrayList<String> getcPos() {
        return cPos;
    }

    public void setcPos(ArrayList<String> cPos) {
        this.cPos = cPos;
    }

    public ArrayList<String> getcDef() {
        return cDef;
    }

    public void setcDef(ArrayList<String> cDef) {
        this.cDef = cDef;
    }
}
