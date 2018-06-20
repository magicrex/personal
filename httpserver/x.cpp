#include<stdlib.h>
#include<string>
#include<iostream>
#include<ctemplate/template.h>
using namespace ctemplate;
int main(int argc,char** argv){
    TemplateDictionary dict( "example");
    dict.SetValue( "NAME" ,  "John Smith"  );
    int  winnings = random() % 100000;
    dict.SetIntValue( "VALUE" , winnings );
    TemplateDictionary *dict1 = dict.AddSectionDictionary( "IN_TABLE"  );
    TemplateDictionary *dict2 = dict.AddSectionDictionary( "IN_TABLE"  );
    dict1->SetValue( "ITEM" ,  "Lihaibo"  );
    dict1->SetFormattedValue( "TAXED_VALUE" ,  "%.2f" , winnings * 0.83 );
    dict2->SetValue( "ITEM" ,  "Qiyuehua"  );
    dict2->SetFormattedValue( "TAXED_VALUE" ,  "%.2f" , winnings * 0.73 );
    if  (1)
    {
        dict.ShowSection( "IN_TABLE"  );

    }
    TemplateDictionary *dict3 = dict.AddIncludeDictionary( "INCLUDED_TEMPLATE"  );
    dict3->SetFilename( "ctInclude.tpl"  );    
    dict3->SetValue( "INCLUDE_VAR" , "This is a include template."  );
    Template* tpl = Template::GetTemplate( "ctexample.tpl",DO_NOT_STRIP);
    std::string output;
    tpl->Expand(&output,&dict);
    std::cout<<output;
    Template::ClearCache();
    return 0;
}
