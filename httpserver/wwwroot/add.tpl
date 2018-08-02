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
    </script>
<title>{{USERNAME}}的主页</title>
</head>
<body>
<div class="mdui-panel mdui-panel-popout" mdui-panel>

  <div class="mdui-panel-item mdui-panel-item-open">
    <div class="mdui-panel-item-header">个人简历</div>
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
    <div class="mdui-card" style="height: 250px">
    <label style="position: relative;left: 5%;top: 20px">添加一个新简历：</label><br>
        <form action="upfile_cgi" method="post" id="uploadForm" enctype="multipart/form-data" style="position: relative;left: 5%;top: 20px" >
            <input id="file" type="file" name="file"/>
            <button id="upload" type="button" onclick="up()" style="position: relative;left: 5%;top: 80px">确定</button>
        </form>
    <label style="position: relative;left: 5%;top: 20px">{{UPMESS}}</label>
    <br>
    <from action="" method="post" name="message" >
    <lable style="position: relative;left: 5%;top: 40px">简介：</lable><br>
    <textarea id="xmessage" rows="3" cols="30" style="position: relative;left: 5%;top: 50px"> 
    </textarea><br>
    <label style="position: relative;left: 5%;top: 50px">{{MESSMESS}}</label>
    <br>
    <button id="upload" type="button" style="position: relative;left: 5%;top: 80px">确定</button>
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
