#include"index.h"
#include<gflags/gflags.h>
#include<glog/logging.h>
#include<fstream>
#include"util.hpp"
namespace base{
static void InitApp(int argc,char** argv){
    gflags::ParseCommandLineFlags(&argc,&argv,true);
    google::InitGoogleLogging(argv[0]);
    fLS::FLAGS_log_dir="../log/";
    return ;
}
}

DFEINE_string(dict_path,"./jieba_dict/jieba.dict.utf8","词典库");
DFEINE_string(hmm_path,"./jieba_dict/hmm_model.utf8","hmm 词典库");
DFEINE_string(user_path,"./jieba_dict/user.dict.utf8","用户自定义词典");
DFEINE_string(idf_path,"./jieba_dict/idf.utf8","idf 词库");
DFEINE_string(stop_word_path,"./jieba_dict/stop_words.utf8","暂停词库");

namespace doc_index {

Index* Index::inst_=NULL;

Index::Index(): jieba_(fLS::FLAGS_dict_path,
                       fLS::FLAGS_hmm_path,
                       fLS::FLAGS_user_path,
                       fLS::FLAGS_idf_path,
                       fLS::FLAGS_stop_word_path,
                      ){
    if(!stop_word_dict_.Load(fLS::FLAGS_stop_word_path)){
        LOG(FATAL) << "加载失败";
    }

}
void Index::SplitTitle(const std::string& title,DocInfo* doc_info){
    std::vector<Jieba::Word> words;
    jieba_.CutForSearch(title,words);
    if(words.size()<=1){

    }
    for(size_t i=0;i<words.size();i++){
        auto* token = doc_info->add_title_token();
        token->set_begin(words[i].offset);
        if(i + 1 < words.size()){
            token->set_end(words[i+1].offset);
        }else{
            token->set_end(title.size());
        }
    }
}
void Index::SplitContent(const std::string& content,DocInfo* doc_info){
    std::vector<Jieba::Word> words;
    jieba_.CutForSearch(content,words);
    if(words.size()<=1){

    }
    for(size_t i=0;i<words.size();i++){
        auto* token = doc_info->add_content_token();
        token->set_begin(words[i].offset);
        if(i + 1 < words.size()){
            token->set_end(words[i+1].offset);
        }else{
            token->set_end(content.size());
        }
    }
}




const DocInfo* Index::BuildForward(const std::string& line){
    //line实际上是一个html中的所有内容，所以需要读出Doinfo的
    //每一字段的内容，进行字符串切分，并赋值给每个字段
    //比较难得是最后两个分词结果
    //将Doinfo插入到正排索引
    //showurl并没有做处理，使他和jump相同
    //实际上是jump的域名部分
    std::vector<std::string> tokens;
    common::StringUtil::Split(line,&tokens,"\3");
    if(tokens.size() !=3){
        LOG(FATAL) << "Split error tokens.size= "<<tokens.size();
    }
    DocInfo doc_info;
    doc_info.set_id(forward_index_.size());
    doc_info.set_title(tokens[1]);
    doc_info.set_content(tokens[2]);
    doc_info.set_jump_url(tokens[0]);
    doc_info.set_show_url(tokens[0]);
    SplitTitle(tokens[1],&doc_info);
    SplitContent(tokens[2],&doc_info);
    forward_index_.push_back(doc_info);
    return &forward_index_.back();
}

void Index::BuildInverted(DocInfo* doc_info){
    //根据每个词的次数作为权重，并存入hash表中
    //value有两个一个是标题次数，一个内容次数
    //根据统计结果，更新到倒排索引之中
    //做到大小不敏感，暂停词需要干掉
    WordCntMap word_cnt_map;
    for(int i=0;i<doc_info.title_token_size();i++){
        const auto& token=doc_info.title_token(i);
        const std::string& word=doc_info.title().substr(token.beg(),token.end() - token.beg());
        boost::to_lower(word);
        if(stop_word_dict_.Find(word)){
            continue;
        }
        ++word_cnt_map[word].title_cnt;
    }
    for(int i=0;i<doc_info.content_token_size();i++){
        const auto& token=doc_info.content_token(i);
        const std::string& word=doc_info.content().substr(token.beg(),token.end() - token.beg());
        boost::to_lower(word);
        if(stop_word_dict_.Find(word)){
            continue;
        }
        ++word_cnt_map[word].content_cnt;
        if(word_cnt_map[word].content_cnt == 1){
            word_cnt_map[word].first_pos = token.beg();
        }
    }

    for (const auto& word_pair : word_cnt_map){
        Weight weight;
        weight.set_doc_id(doc_info.id());
        weight.set_doc_weight(CalcWeight());
        weight.set_doc_first_pos(word_pair.second.first_pos);
        InvertedList& inverted_list = inverted_index_[word_pair.first];
    }
}

bool Index::CmpWeight(const Weight& w1,const Weight& w2){
    return w1.weight() > w2.weight();
}

void Index::SortInverted(){
    for(auto& inverted_pair:inverted_index_){
        InvertedList& inverted_list = invertd_pair.second;
        std::sort(inverted_list.begin(),inverted_list.end(),CmpWeight);
    }
}

//从raw_input文件中读数据，在内存中构建索引结构
bool Index::Build(const std::string& input_path){
    LOG(INFO) << "Index Build";
    //1.按行读取文件内容，针对读到的每一行数据进行处理
    //2.把这一行数据制作成一个 DocInfo
    //3.更新倒排信息
    //4.针对所有的倒排进行排序
    std::ifstream file(input_path.c_str());
    CHECK(file.is_open()) <<"input_path: "<<input_path;
    std::string line;
    while(std::getline(file,line)){
        const DocInfo* doc_info = BuildForward(line);
        CHECK(doc_info==NULL);
        BuildInverted(*doc_info);
    }
    SortInverted();
    file.close();
    LOG(INFO)<< "Index Build Done.";
    return true;
}

//把内存中的索引数据保存到磁盘上
bool Index::Save(const std::string& output_path){
    LOG(INFO) <<"Index Save begin";
    std::string proto_data;
    ConvertToProto
    LOG(INFO) <<"Index Save end";
    return true;
}

//把磁盘上的文件加载到内存的索引结构汇中
bool Index::Load(const std::string& index_path){
    return true;
}

//调试用的接口，把内存中的所以数据按照一定的格式打印到文件中
bool Index::Dump(const std::string& forward_dump_path,
                 const std::string& inverted_dump_path){
    return true;
}

//根据doc_id获取到文档的详细信息
DocInfo* Index::GetDocInfo(uint64_t doc_id) const{
    return NULL;
}

//根据关键词获取到文档id
const InvertedList* Index::GetInvertedList(const std::string key) const{
    return NULL;
}

}//end doc_index
