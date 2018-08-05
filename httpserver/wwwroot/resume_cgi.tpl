<html>
<head>
<meta charset="utf-8">
<script src="js/mdui.min.js"></script>
<script src="js/jquery-3.3.1.js"></script>
<link rel="stylesheet" href="css/mdui.min.css">
    <script>
    function Upfile(){
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
    </script>
    <script>
        function Deletefile(){
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
    </script>
    <script>
        function Deletenote(){
            var data=$("#delnote").val();
            $.ajax({
            url: 'delnote_cgi',
            type: 'POST',
            data: date,
            cache: false,
            processData: false,
            contentType: false
                   }).done(function(res){
                    document.writeln(res);
                    }).fail(function(res){
                        document.writeln(res);
                            });
        }
    </script>
    <script>
        function Deleteproj(){
            var data=$("#delproj").val();
            $.ajax({
            url: 'delproj_cgi',
            type: 'POST',
            data: data,
            cache: false,
            processData: false,
            contentType: false
                   }).done(function(res){
                    document.writeln(res);
                    }).fail(function(res){
                        document.writeln(res);
                            });
        }
    </script>
    <script>
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
    <script>
        function Addstu(){
            var mess21=$("#mess21").val();
            var mess22=$("#mess22").val();
            var mess23=$("#mess23").val();
            var mess24=$("#mess24").val();
            var formdata=new FormData();
            formdata.append("title",mess21);
            formdata.append("message",mess22);
            formdata.append("class",mess23);
            formdata.append("url",mess24);
            $.ajax({
            url: 'addstu_cgi',
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
    <script>
        function Addpro(){
            var mess31=$("#mess31").val();
            var mess32=$("#mess32").val();
            var mess33=$("#mess33").val();
            var mess34=$("#mess34").val();
            var mess35=$("#mess35").val();
            var mess36=$("#mess36").val();
            var formdata=new FormData();
            formdata.append("pro_title",mess31);
            formdata.append("pro_message",mess32);
            formdata.append("pro_env",mess33);
            formdata.append("pro_func",mess34);
            formdata.append("pro_flow",mess35);
            formdata.append("pro_url",mess36);
            $.ajax({
            url: 'addpro_cgi',
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
        <script>
        function doset(){
            var checkID = [];
            var resu=$("#setresu").val();
             var formdata=new FormData();
            formdata.append("setresu",resu);
            $("input[name='check']:checked").each(function(i){
              checkID[i] =$(this).val();
            formdata.append("setproj",checkID[i]);
             });
            $.ajax({
            url: 'set_cgi',
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
    <div class="mdui-panel-item-header">
    <div class="mdui-panel-item-title">个人简历</div>
    <i class="mdui-panel-item-arrow mdui-icon material-icons">keyboard_arrow_down</i>
    </div>
    <div class="mdui-panel-item-body">
    <div class="mdui-table-fluid">
        <table class="mdui-table">
        <thead>
            <th>标题</th>
            <th>操作</th>
            <th>备注</th>
            <th>日期</th>
        </thead>
        {{#RESUME}}
        <tbody>
        <tr>
            <td>{{value1}}</td>
            <td><a href="{{value2}}" dowmload="{{value1}}" >下载</a></td>
            <td>{{value3}}</td>
            <td>{{value4}}</td>
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
        <button id="upload" type="button" onclick="Upfile()" >确定</button><br>
        </form>
    <br>
    <from action="delfile_cgi" method="DELETE" style="position: relative;left: 5%;top: 60px">
        <lable>需要删除的文件:</lable><br>
        <select id="delfile"  name="delfile">
        {{#DELFILE}}
        <option value="{{value1}}">{{value1}}</option>
        {{/DELFILE}}
        </select><br>
        <label >{{DELFMESS}}</label><br>
        <input type="button" value="删除" name="delf" onclick="Deletefile()" >
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
    <div class="mdui-panel-item-header">
    <div class="mdui-panel-item-title">学习笔记</div>
    <i class="mdui-panel-item-arrow mdui-icon material-icons">keyboard_arrow_down</i>
    </div>
    <div class="mdui-panel-item-body">
        <div class="mdui-table-fluid">
        <table class="mdui-table">
        <thead>
            <th>标题</th>
            <th>地址</th>
            <th>简介</th>
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
    <div class="mdui-divider-dark" style="height: 10px"></div>
    <div class="mdui-card" style="overflow-y: auto;height: 550px">
        <from>
        <lable style="font-weight: 400">添加一个链接:</lable>
        <div class="mdui-textfield">
              <label class="mdui-textfield-label">标题</label>
                <textarea  id="mess21" Class="mdui-textfield-input"></textarea>
        </div>
        <div class="mdui-textfield">
              <label class="mdui-textfield-label">简介</label>
                <textarea id="mess22" class="mdui-textfield-input"></textarea>
        </div>
        <div class="mdui-textfield">
              <label class="mdui-textfield-label">分类</label>
                <textarea id="mess23" class="mdui-textfield-input"></textarea>
        </div>
        <div class="mdui-textfield">
              <label class="mdui-textfield-label">链接</label>
                <textarea id="mess24" class="mdui-textfield-input"></textarea>
        </div>
        <button id="addstu" class="mdui-btn mdui-ripple" style="margin-left: 90%" onclick="Addstu()">确定</button>
        </from>
        <br>
        <br>
        <br>
        <from action="delnote_cgi" method="DELETE" style="position: relative;left: 5%;top: 50px">
        <lable>需要删除的笔记:</lable><br>
        <select id="delnote"  name="delnote">
        {{#DELNOTE}}
        <option value="{{value1}}">{{value1}}</option>
        {{/DELNOTE}}
        </select><br>
        <label >{{DELNMESS}}</label><br>
        <input type="button" value="删除" name="deln" onclick="Deletenote()" >
    </from>
    </div>
    </div>
  </div>
   
  <div class="mdui-panel-item">
    <div class="mdui-panel-item-header">
    <div class="mdui-panel-item-title">项目练习</div>
    <i class="mdui-panel-item-arrow mdui-icon material-icons">keyboard_arrow_down</i>
    </div>
    <div class="mdui-panel-item-body">

        {{#PROJECT}}
        <div class="mdui-panel" mdui-panel>
            <div class="mdui-panel-item">
            <div class="mdui-panel-item-header">{{value1}}</div>
            <div class="mdui-panel-item-body">

                <div class="mdui-panel" mdui-panel>
                    <div class="mdui-panel-item">
                    <div class="mdui-panel-item-header">项目简介</div>
                    <div class="mdui-panel-item-body">
                        <p>{{value2}}</p>
                    </div>
                    </div>
                </div>
                <div class="mdui-panel" mdui-panel>
                    <div class="mdui-panel-item">
                    <div class="mdui-panel-item-header">运行环境</div>
                    <div class="mdui-panel-item-body">
                        <p>{{value3}}</p>
                    </div>
                    </div>
                </div>
                <div class="mdui-panel" mdui-panel>
                    <div class="mdui-panel-item">
                    <div class="mdui-panel-item-header">项目功能</div>
                    <div class="mdui-panel-item-body">
                        <p>{{value4}}</p>
                    </div>
                    </div>
                </div>
                <div class="mdui-panel" mdui-panel>
                    <div class="mdui-panel-item">
                    <div class="mdui-panel-item-header">核心流程</div>
                    <div class="mdui-panel-item-body">
                        <p>{{value5}}</p>
                    </div>
                    </div>
                </div>
                <div class="mdui-panel" mdui-panel>
                    <div class="mdui-panel-item">
                    <div class="mdui-panel-item-header">相关链接</div>
                    <div class="mdui-panel-item-body">
                        <p>{{value6}}</p>
                    </div>
                    </div>
                </div>

            </div>
            </div>
        </div>
        {{/PROJECT}}

        <div class="mdui-divider-dark" style="height: 10px"></div>
        <div class="mdui-card" style="overflow-y: auto;height: 700px">
        <from>
        <lable style="font-weight: 400">添加一个项目:</lable>
        <div class="mdui-textfield">
              <label class="mdui-textfield-label">项目名称</label>
                <textarea id="mess31" Class="mdui-textfield-input"></textarea>
        </div>
        <div class="mdui-textfield">
              <label class="mdui-textfield-label">项目简介</label>
                <textarea id="mess32" class="mdui-textfield-input"></textarea>
        </div>
        <div class="mdui-textfield">
              <label class="mdui-textfield-label">运行环境</label>
                <textarea id="mess33" class="mdui-textfield-input"></textarea>
        </div>
        <div class="mdui-textfield">
              <label class="mdui-textfield-label">项目功能</label>
                <textarea id="mess34" class="mdui-textfield-input"></textarea>
        </div>
        <div class="mdui-textfield">
              <label class="mdui-textfield-label">核心流程</label>
                <textarea id="mess35" class="mdui-textfield-input"></textarea>
        </div>
        <div class="mdui-textfield">
              <label class="mdui-textfield-label">相关链接</label>
                <textarea id="mess36" class="mdui-textfield-input"></textarea>
        </div>
        <button id="addpro" class="mdui-btn mdui-ripple" style="margin-left: 90%" onclick="Addpro()">确定</button>
        </from>
        <br>
        <br>
        <from action="deproj_cgi" method="DELETE" style="position: relative;left: 5%;top: 50px">
        <lable>需要删除的项目:</lable><br>
        <select id="delproj"  name="delproj">
        {{#DELPROJ}}
        <option value="{{value1}}">{{value1}}</option>
        {{/DELPROJ}}
        </select><br>
        <label >{{DELPMESS}}</label><br>
        <input type="button" value="删除" name="delp" onclick="Deleteproj()" >
    </from>
    </div>
    </div>
    </div>
    
    <div class="mdui-panel-item">
    <div class="mdui-panel-item-header">
    <div class="mdui-panel-item-title">设置显示</div>
    <i class="mdui-panel-item-arrow mdui-icon material-icons">keyboard_arrow_down</i>
    </div>
    <div class="mdui-panel-item-body">
     <div class="mdui-card" style="overflow-y: auto;height: 200px">
        <from action="set_cgi" method="POST" style="position: relative;left: 5%;top: 50px">
        <lable>选择一个简历进行展示：</lable>
        <select id="setresu" name="setresu">
        {{#SETRESU}}
        <option value="{{value1}}">{{value1}}</option>
        {{/SETRESU}}
        </select>
        </from>
        <br>
        <label style="position: relative;left: 5%;top: 50px">笔记默认为全部展示</label>
        <br>
        <from action="set_cgi" method="POST" style="position: relative;left: 5%;top: 50px">
        <lable>选择多个项目进行展示：</lable><br>
        {{#SETPROJ}}
        <lable>{{value1}}</lable><input type="checkbox" name="check" value="{{value1}}" /><br>
        {{/SETPROJ}}
        </from>
        <br>
        <lable style="position: relative;left: 5%;top: 50px">{{SETMESS}}</lable><br>
        <input style="position: relative;left: 5%;top: 50px" type="button" value="确定" id="Doset" onclick="doset()">

    </div>
    </div>
    </div>



</div>
</body>
</html>
