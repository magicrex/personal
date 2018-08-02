<!--index.tpl-->
<!doctype html>
<html>
<head>
<meta charset="utf-8">
<link rel="stylesheet" href="css/mdui.min.css">
<script src="js/mdui.min.js"></script>
<script src="js/jquery-3.3.1.js"></script>
    <script>
    function up(){
        var data = new FormData($('#uploadForm')[0])
        $.ajax({
            url: 'upfile_cgi',
            type: 'POST',
            cache: false,
            data: data,
            processData: false,
            contentType: false
            }).done(function(res){
                    document.writeln(res);
                    }).fail(function(res){
                        document.writeln(res);
                            });
    }
        function Deletefun(){
            var data=$("#delfile").val();
            $.ajax({
            url: data,
            type: 'DELETE',
            cache: false,
            processData: false,
            contentType: false
                   }).done(function(res){
                    document.writeln(res);
                    }).fail(function(res){
                        document.writeln(res);
                            });
        }
        function Modimess(){
            var name=$("#modimess").val();
            var nei=$("#xmessage").val();
            var formdata=new FormData();
            formdata.append("filename",name);
            formdata.append("message",nei);
            $.ajax({
            url: 'modimess_cgi',
            type: 'POST',
            cache: false,
            data: formdata,
            processData: false,
            contentType: false
                   }).done(function(res){
                    document.writeln(res);
                    }).fail(function(res){
                        document.writeln(res);
                            });
        }
    </script>
<title>{{USERNAME}}的主页</title>
</head>
<body>
<div class="mdui-panel mdui-panel-popout" mdui-panel>

  <div class="mdui-panel-item">
    <div class="mdui-panel-item-header">个人简历</div>
    <div class="mdui-panel-item-body">
    <div class="mdui-table-fluid">
        <table class="mdui-table">
        <thead>
            <th>标题</th>
            <th>操作</th>
            <th>备注</th>
            <th>分类</th>
            <th>日期</th>
        </thead>
        {{#RESUME}}
        <tbody>
        <tr>
            <td>{{value1}}</td>
            <td><a href="{{value2}}" dowmload="{{value1}}" >下载</a></td>
            <td>{{value3}}</td>
            <td>{{value4}}</td>
            <td>{{value5}}</td>
        </tr>
        </tbody>
        {{/RESUME}}
        </table>
    </div>
    <div class="mdui-divider-dark" style="height: 10px"></div>
    <div class="mdui-card" style="height: 500px">
    <form action="upfile_cgi" method="post" id="uploadForm" enctype="multipart/form-data" style="position: relative;left: 5%;top: 20px" >
        <label >添加一个新简历：</label><br>
        <input id="file" type="file" name="file"/><br>
        <label >{{UPMESS}}</label><br>
        <button id="upload" type="button" onclick="up()" >确定</button><br>
        </form>
    <br>
    <from action="delfile_cgi" method="DELETE" style="position: relative;left: 5%;top: 60px">
        <lable>需要删除的文件:</lable><br>
        <select id="delfile"  name="delfile">
        {{#DELFILE}}
        <option value="{{value1}}">{{value1}}</option>
        {{/DELFILE}}
        </select><br>
        <label >{{DELMESS}}</label><br>
        <input type="button" value="删除" name="delf" onclick="Deletefun()" >
    </from>
    <br>
    <from action="modimess_cgi" method="post" id="amessage" name="amessage" style="position: relative;left: 5%;top: 100px">
        <lable>修改的文件:</lable><br>
        <select id="modimess"  name="modimess">
        {{#MODIMESS}}
        <option value="{{value1}}">{{value1}}</option>
        {{/MODIMESS}}
        </select><br>
        <lable >修改简介：</lable><br>
            <textarea id="xmessage" name="xmessage" rows="3" cols="30" > 
            </textarea><br>
        <label>{{MESSMESS}}</label><br>
        <input type="button" value="修改" name="modim" onclick="Modimess()">
    </from>
    </div>
      
    </div>
  </div>
  
  <div class="mdui-panel-item">
    <div class="mdui-panel-item-header">学习笔记</div>
    <div class="mdui-panel-item-body">
        <div class="mdui-table-fluid">
        <table class="mdui-table">
        <thead>
            <th>标题</th>
            <th>地址</th>
            <th>备注</th>
            <th>分类</th>
            <th>日期</th>
        </thead>
        {{#NOTES}}
        <tbody>
        <tr>
            <td>{{value1}}</td>
            <td>{{value2}}</td>
            <td>{{value3}}</td>
            <td>{{value4}}</td>
            <td>{{value5}}</td>
        </tr>
        </tbody>
        {{/NOTES}}
        </table>
    </div>
    </div>
  </div>
  
  <div class="mdui-panel-item">
    <div class="mdui-panel-item-header">项目练习</div>
    <div class="mdui-panel-item-body">
      <div class="mdui-table-fluid">
        <table class="mdui-table">
        <thead>
            <th>标题</th>
            <th>地址</th>
            <th>备注</th>
            <th>分类</th>
            <th>日期</th>
        </thead>
        {{#PROJECT}}
        <tbody>
        <tr>
            <td>{{value1}}</td>
            <td>{{value2}}</td>
            <td>{{value3}}</td>
            <td>{{value4}}</td>
            <td>{{value5}}</td>
        </tr>
        </tbody>
        {{/PROJECT}}
        </table>
    </div>
    </div>
  </div>
  
</div>
    

</body>
</html>
