package javaDictionary;

import com.google.common.collect.ArrayListMultimap;
import com.google.common.collect.Multimap;
import java.util.*;

public class JavaDictionary implements DictionaryInterface{
    //because there is no pair class in Java
    static class FullDef{
        String mPos;
        String mDef;

        FullDef(String mPos, String mDef)
        {
            this.mPos = mPos;
            this.mDef = mDef;
        }
        //for outputting the fullDef in our program
        @Override
        public String toString(){
            return "[" + this.mPos + "]: " + this.mDef;
        }
        //need to override the equals function so it actually works for distinct function
        @SuppressWarnings("EqualsWhichDoesntCheckParameterClass")
        @Override
        public boolean equals(Object o)
        {
            FullDef check = (FullDef) o;
            return this.mPos.equals(check.mPos) && this.mDef.equals(check.mDef);
        }

    }

    //load in from the enum database by creating a multimap and placing all values in using a loop
    public Multimap<String, FullDef> load()
    {
        //strings for loading in data
        System.out.println("! Loading data...");
        Multimap<String, FullDef> dictionaryMM = ArrayListMultimap.create();
        for (EntryDatabase entry: EntryDatabase.values())
        {
            //convert the enum name so that it is first letter uppercase and rest lowercase
            String name = entry.name().substring(0,1).toUpperCase() + entry.name().substring(1).toLowerCase();
            Iterator<String> iPos = (entry.getcPos()).iterator();
            Iterator<String> iDef = (entry.getcDef()).iterator();
            while(iPos.hasNext() && iDef.hasNext())
            {
                dictionaryMM.put(name, new FullDef(iPos.next(),iDef.next()));
            }
        }
        //strings for once data is loaded
        System.out.println("! Loading completed...");
        System.out.println("\n");
        System.out.println("===== DICTIONARY 340 JAVA =====");
        System.out.println("----- Keywords: " + dictionaryMM.keySet().size());
        System.out.println("----- Definitions: " + dictionaryMM.size() + "\n");
        return dictionaryMM;
    }

    public static void run()
    {
        //define all instances of objects - JavaDictionary, Multimap, and Scanner
        JavaDictionary currentDict = new JavaDictionary();
        Multimap<String,FullDef> currentDictData = currentDict.load();
        Scanner sc = new Scanner(System.in);
        //times a user inputs something
        int numInputs = 1;
        //get first instance of Scanner
        System.out.printf("Search [%d]: ",numInputs);
        String query = sc.nextLine();
        query = query.trim();
        query = query.toLowerCase();
        //the while loop that does the work
        while (!query.equals(ActionDatabase.QUIT.getcName()))
        {
            Queue<String> valid_input = currentDict.error_handling(currentDictData, query);
            currentDict.input_handling(currentDictData,valid_input);
            numInputs++;
            System.out.printf("Search [%d]: ",numInputs);
            query = sc.nextLine();
            query = query.trim();
            query = query.toLowerCase();
        }
        System.out.println("-----THANK YOU-----");
    }

    public Queue<String> error_handling(Multimap<String,FullDef> DictData,String query)
    {
        //turn our query into a queue and make an index counter for handling errors or adding to valid input
        Queue<String> queryQu = new LinkedList<>(Arrays.asList(query.split(" ", 0)));
        Queue<String> output = new LinkedList<>();
        int queryQu_counter = 1;
        if (queryQu.size() > 4)
        {
            output.add(null);
            return output;
        }
        while(!queryQu.isEmpty())
        {
            switch (queryQu_counter){
                //keyword or help or quit or empty (which is still help)
                case 1 ->
                {
                    //remove whitespace (leading or trailing whitespace)
                    String potentialKW_UF = queryQu.poll().replaceAll("\\s+","");
                    String potentialKW_F = null;
                    if (!potentialKW_UF.isEmpty())
                        potentialKW_F = potentialKW_UF.substring(0,1).toUpperCase() + potentialKW_UF.substring(1).toLowerCase();
                    if (DictData.containsKey(potentialKW_F) || potentialKW_UF.equals(ActionDatabase.QUIT.getcName())
                            || potentialKW_UF.equals(ActionDatabase.HELP.getcName()) || potentialKW_UF.isEmpty())
                    {
                        output.add(potentialKW_F);
                    }
                    queryQu_counter++;
                }
                case 2 ->
                {
                    String potentialAW_F = queryQu.poll().replaceAll("\\s+","");
                    boolean valid = false;
                    for (ActionDatabase entry: ActionDatabase.values())
                    {
                        if (entry.getcName().equals(potentialAW_F) && !potentialAW_F.equals(ActionDatabase.QUIT.getcName())
                        && !potentialAW_F.equals(ActionDatabase.HELP.getcName()))
                        {
                            output.add(potentialAW_F);
                            valid = true;
                        }
                    }
                    if (!valid)
                    {
                        invalid_action(potentialAW_F,queryQu_counter);
                    }
                    queryQu_counter++;
                }
                case 3 ->
                {
                    String potentialAW_F = queryQu.poll().replaceAll("\\s+","");
                    boolean valid = false;
                    if (potentialAW_F.equals(ActionDatabase.REVERSE.getcName()) || potentialAW_F.equals(ActionDatabase.DISTINCT.getcName()))
                    {
                            output.add(potentialAW_F);
                            valid = true;
                    }
                    if (!valid)
                    {
                        invalid_action(potentialAW_F,queryQu_counter);
                    }
                    queryQu_counter++;
                }
                case 4 ->
                {
                    String potentialAW_F = queryQu.poll().replaceAll("\\s+","");
                    boolean valid = false;
                    if (potentialAW_F.equals(ActionDatabase.REVERSE.getcName()))
                    {
                        output.add(potentialAW_F);
                        valid = true;
                    }
                    if (!valid)
                    {
                        invalid_action(potentialAW_F,queryQu_counter);
                    }
                    queryQu_counter++;
                }
                default ->
                {
                    queryQu.poll();
                    output.clear();
                }
            }
        }
        return output;
    }

    public void input_handling(Multimap<String, FullDef> DictData,Queue<String> query)
    {
        Multimap<String,FullDef>output = ArrayListMultimap.create();
        boolean help = false;
        while (!query.isEmpty())
        {
            String current = query.poll();
            if (Objects.isNull(current))
            {
                help();
                help = true;
            }
            else if (DictData.containsKey(current))
            {
                output = keyword(DictData,current);
            }
            else if(current.equals(ActionDatabase.HELP.getcName()))
            {
                help();
                help = true;
            }
            else if (current.equals(ActionDatabase.DISTINCT.getcName()))
            {
                output = distinct(output);
            }
            else if (current.equals(ActionDatabase.REVERSE.getcName()))
            {
                output = reverse(output);
            }
            else
            {
                output = POS(output,current);
            }
        }
        if(output.isEmpty() && help)
        {
        }
        else if (output.isEmpty() && !help)
        {
            invalid_entry();
        }
        else
        {
            print(output);
        }
    }

    // main function
    public static void main (String[] args)
    {
        run();
    }

    @Override
    public Multimap<String, FullDef> keyword(Multimap<String, FullDef> DictMM, String keyword) {
        Multimap<String,FullDef> output = ArrayListMultimap.create();
        for (Map.Entry<String,FullDef> entry : DictMM.entries())
        {
            if (entry.getKey().equalsIgnoreCase(keyword))
            {
                output.put(entry.getKey(),entry.getValue());
            }
        }
        return output;
    }

    @Override
    public Multimap<String, FullDef> distinct(Multimap<String, FullDef> DictMM){
        Multimap<String,FullDef> output = ArrayListMultimap.create();
        for (Map.Entry<String,FullDef> entry: DictMM.entries())
        {
            if (!output.containsEntry(entry.getKey(),entry.getValue()))
            {
                output.put(entry.getKey(),entry.getValue());
            }
        }
        return output;
    }

    @Override
    public Multimap<String, FullDef> reverse(Multimap<String, FullDef> DictMM) {
        Stack<Map.Entry<String,FullDef>> reverse_stack = new Stack<>();
        Multimap<String,FullDef> output = ArrayListMultimap.create();
        for (Map.Entry<String,FullDef> entry: DictMM.entries())
        {
            reverse_stack.push(entry);
        }
        while(!reverse_stack.isEmpty())
        {
            Map.Entry<String,FullDef> current = reverse_stack.pop();
            output.put(current.getKey(),current.getValue());
        }
        return output;
    }

    @Override
    public void help() {
        System.out.println("""
                |
                PARAMETER HOW-TO, please enter:
                1. A search key -then 2. An optional part of speech -then
                3. An optional 'distinct' -then 4. An optional 'reverse'
                |""");
    }

    @Override
    public Multimap<String, FullDef> POS(Multimap<String, FullDef> DictMM, String pos) {
        Multimap<String,FullDef> output = ArrayListMultimap.create();
        for (Map.Entry<String,FullDef> entry : DictMM.entries())
        {
            if (entry.getValue().mPos.equalsIgnoreCase(pos))
            {
                output.put(entry.getKey(),entry.getValue());
            }
        }
        return output;
    }

    @Override
    public void print(Multimap<String, FullDef> DictMM) {
        System.out.println("|");
        for (Map.Entry<String, FullDef> entry: DictMM.entries())
        {
            System.out.println(entry.getKey() + " " + entry.getValue());
        }
        System.out.println("|");
    }

    @Override
    public void invalid_entry(){
        System.out.println("""
                |
                <NOT FOUND> To be considered for the next release. Thank you.
                |""");
        help();
    }

    @Override
    public void invalid_action(String invalid_action, int n){
        switch (n) {
            case 1 -> invalid_entry();
            case 2 -> {
                String output2 = "|\n"
                        + "<The entered 2nd parameter '" + invalid_action + "' is NOT a part of speech.>\n"
                        + "<The entered 2nd parameter '" + invalid_action + "' is NOT 'distinct'.>\n"
                        + "<The entered 2nd parameter '" + invalid_action + "' is NOT 'reverse'.>\n"
                        + "<The entered 2nd parameter '" + invalid_action + "' was disregarded.>\n"
                        + "<The " + n + "nd parameter should be a part of speech or 'distinct' or 'reverse'.>\n"
                        + "|";
                System.out.println(output2);
            }
            case 3 -> {
                String output3 = "|\n"
                        + "<The entered 3rd parameter '" + invalid_action + "' is NOT 'distinct'.>\n"
                        + "<The entered 3rd parameter '" + invalid_action + "' is NOT 'reverse'.>\n"
                        + "<The entered 3rd parameter '" + invalid_action + "' was disregarded.>\n"
                        + "<The 3rd parameter should be 'distinct' or 'reverse'.>\n"
                        + "|";
                System.out.println(output3);
            }
            default -> {
                String output4 = "|\n"
                        + "<The entered 4th parameter '" + invalid_action + "' is NOT 'reverse'.>\n"
                        + "<The entered 4th parameter '" + invalid_action + "' was disregarded.>\n"
                        + "<The 4th parameter should be 'distinct' or 'reverse'.>\n"
                        + "|";
                System.out.println(output4);
            }
        }
    }
}