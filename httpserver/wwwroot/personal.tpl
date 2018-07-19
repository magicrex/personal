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
<title>{{USERNAME}}主页</title>
</head><ul></ul>

<body>
<div class="mdui-tab" mdui-tab>
  <a href="#example1-tab1" class="mdui-ripple tab1">个人简历</a>
  <a href="#example1-tab2" class="mdui-ripple tab2">学习笔记</a>
  <a href="#example1-tab3" class="mdui-ripple tab3">项目练习</a>
</div>
<!--标签1-->
<div id="example1-tab1" class="mdui-p-a-2">
	<div class="mdui-table-fluid">
		{{#RESUME}}
		<table class="mdui-table">
		<tbody>
		<tr>
			<td>{{value1}}</td>
			<td>{{value2}}</td>
			<td>{{value3}}</td>
			<td>{{value4}}</td>
			<td>{{value5}}</td>
		</tr>
		</tbody>
		</table>
		{{/RESUME}}
	</div>
	<div class="mdui-divider-dark" style="height: 10px"></div>
	<div class="mdui-card" style="height: 350px">
	<label style="position: relative;left: 5%;top: 20px">添加一个新文件：</label><br>
	<from action="" method="post" name="files" style="position: relative;left: 5%;top: 20px">
		<input type="file" name="File1">
	</from>
	<br>
	<from action="" method="post" name="message" >
	<lable style="position: relative;left: 5%;top: 50px">简介：</lable><br>
	<textarea rows="10" cols="30" style="position: relative;left: 5%;top: 60px"> 
	</textarea><br>
	<button style="position: relative;left: 5%;top: 80px">确定</button>
	</from>
	</div>
</div>
<!--标签2-->
<div id="example1-tab2" class="mdui-p-a-2">

</div>
<!--标签3-->
<div id="example1-tab3" class="mdui-p-a-2">

</div>

</body>
</html>
