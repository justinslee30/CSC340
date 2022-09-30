package javaDictionary;

import com.google.common.collect.Multimap;

public interface DictionaryInterface {
    //keyword: return a smaller multimap where keyword is specified, if keyword not in currentDictData, then return error and invoke help
    //always first function invoked if any word except !help in the scanner - DONE
    Multimap<String, JavaDictionary.FullDef> keyword(Multimap<String,JavaDictionary.FullDef> DictMM, String keyword);
    //distinct: return a smaller multimap where each value is distinct, maybe .values().stream().distinct() - DONE
    Multimap<String, JavaDictionary.FullDef> distinct(Multimap<String,JavaDictionary.FullDef> DictMM);
    //reverse: return a smaller multimap where it takes a multimap and reverses it - DONE
    Multimap<String,JavaDictionary.FullDef> reverse(Multimap<String,JavaDictionary.FullDef> DictMM);
    //help: brings up help - DONE
    void help();
    //the group of functions below return a smaller multimap where it loops through it, looks for the POS
    //(between the brackets) and only extracts the one where POS is correct - DONE
    Multimap<String,JavaDictionary.FullDef> POS(Multimap<String,JavaDictionary.FullDef> DictMM, String pos);
    //print: print the entry, will be called at end - DONE
    void print(Multimap<String,JavaDictionary.FullDef> DictMM);
    //invalid_entry: prints error message when a word search is not found in the dictionary
    void invalid_entry();
    //invalid_action: prints out error message when a word that is not an action word is used
    void invalid_action(String invalid_action, int n);
}
