#include"index.h"
#include<gflags/gflags.h>
#include<glog/logging.h>
#include<fstream>

namespace base{
static void InitApp(int argc,char** argv){
    gflags::ParseCommandLineFlags(&argc,&argv,true);
    google::InitGoogleLogging(argv[0]);
    fLS::FLAGS_log_dir="../log/";
    return ;
}
}


namespace doc_index {

Index* Index::inst_=NULL;

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
