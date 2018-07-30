<!doctype html>
<html>
<head>
<meta charset="utf-8">
<link rel="stylesheet" href="css/mdui.min.css">
<style>
	.mdui-tab{
		background:#F93;
	}
</style>
<script src="js/mdui.min.js"></script>
    <script src="js/jquery-3.3.1.js"></script>
<title>{{USERNAME}}的主页</title>
</head>

<body>
<div class="mdui-tab" mdui-tab>
  <a href="#example1-tab1" class="mdui-ripple tab1">个人简历</a>
  <a href="#example1-tab2" class="mdui-ripple tab2">学习笔记</a>
  <a href="#example1-tab3" class="mdui-ripple tab3">项目练习</a>
</div>
<!--标签1-->
<div id="example1-tab1" class="mdui-p-a-2">
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
			<td>{{value2}}</td>
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
        <form id="uploadForm" enctype="multipart/form-data" style="position: relative;left: 5%;top: 20px" >
            <input id="file" type="file" name="file"/>
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

    <script>
    $('button').click(function(){
        var message = $("#xmessage").val()
        var data = new FormData($('#uploadForm')[0])
        $.ajax({
            url: 'upfile_cgi',
            type: 'POST',
            cache: false,
            data: data,
            processData: false,
            contentType: false
        }).done(function(res) {
        }).fail(function(res) {});

    });
</script>
	</div>
</div>
<!--标签2-->
<div id="example1-tab2" class="mdui-p-a-2">
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
<!--标签3-->
<div id="example1-tab3" class="mdui-p-a-2">
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
</body>
</html>
