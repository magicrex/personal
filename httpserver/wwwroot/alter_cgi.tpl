<!--index.tpl-->
<!doctype html>
<html>
<head>
<meta charset="utf-8">
<link rel="stylesheet" href="css/mdui.min.css">
<script src="js/mdui.min.js"></script>
<title>首页</title>
</head>


<body>
<div style="display: inline; margin-left:0px;margin-top:0px;width: 100%">

<div class="mdui-card" style=" display: inline-block;width:48%;height: 25%">
<div class="mdui-card-media" >
<img src="./images/1.jpg"/>
<div class="mdui-card-media-covered">
<div class="mdui-card-primary">
<div class="mdui-panel" mdui-panel style="background:#000; filter:alpha(opacity:30); opacity:0.5">
<div class="mdui-panel-item">
<div class="mdui-panel-item-header">
<div class="mdui-panel-item-title">登录</div>
<i class="mdui-panel-item-arrow mdui-icon material-icons">+</i>
</div>
<div class="mdui-panel-item-body">
<form action="login_cgi" method="post">        
<div class="mdui-textfield mdui-textfield-floating-label">
<label class="mdui-textfield-label">账号</label>
<input class="mdui-textfield-input" type="text" name="username" />
</div>
<div class="mdui-textfield mdui-textfield-floating-label">
<label class="mdui-textfield-label">密码</label>
<input class="mdui-textfield-input" type="password" name="password" />
</div>
<div class="mdui-panel-item-actions">
<button class="mdui-btn mdui-ripple" type="reset" mdui-panel-item-close>取消</button>
<button class="mdui-btn mdui-ripple" >确定</button>
</div>
</form>
</div>
</div>  
</div>
</div>
</div>
</div>
</div>

<div class="mdui-card" style=" display: inline-block;width:48%;height: 25%">
<div class="mdui-card-media">
<img src="./images/2.jpg"/>
<div class="mdui-card-media-covered">
<div class="mdui-card-primary">
<div class="mdui-panel" mdui-panel style="background:#000; filter:alpha(opacity:30); opacity:0.5">
<div class="mdui-panel-item">
<div class="mdui-panel-item-header">
<div class="mdui-panel-item-title">查询</div>
<i class="mdui-panel-item-arrow mdui-icon material-icons">+</i>
</div>
<div class="mdui-panel-item-body">
<form action="select_cgi" method="post">
<div class="mdui-textfield mdui-textfield-floating-label">
<label class="mdui-textfield-label">账号</label>
<input class="mdui-textfield-input" type="text" name="username" required/>
<div class="mdui-textfield-error">账号不能为空</div>
</div>
<div class="mdui-panel-item-actions">
<button class="mdui-btn mdui-ripple" mdui-panel-item-close>取消</button>
<button class="mdui-btn mdui-ripple">确定</button>
</div>
</form>
</div>
</div>  
</div>
</div>
</div>
</div>
</div>

<div class="mdui-card" style="display: inline-block;width:48%;height: 25%">
<div class="mdui-card-media">
<img src="./images/4.jpg"/>
<div class="mdui-card-media-covered">
<div class="mdui-card-primary">
<div class="mdui-panel" mdui-panel style="background:#000; filter:alpha(opacity:30); opacity:0.5">
<div class="mdui-panel-item">
<div class="mdui-panel-item-header">
<div class="mdui-panel-item-title">注册</div>
<i class="mdui-panel-item-arrow mdui-icon material-icons">+</i>
</div>
<div class="mdui-panel-item-body">
<form action="regist_cgi" method="post">
<div class="mdui-textfield mdui-textfield-floating-label">
<label class="mdui-textfield-label">账号</label>
<input class="mdui-textfield-input" type="text" name="username" required/>
<div class="mdui-textfield-error">账号不能为空</div>
</div>
<div class="mdui-textfield mdui-textfield-floating-label">
<label class="mdui-textfield-label">邮箱</label>
<input class="mdui-textfield-input" type="email" name="email" required/>
<div class="mdui-textfield-error">邮箱格式错误/div>
</div>
<div class="mdui-textfield mdui-textfield-floating-label">
<label class="mdui-textfield-label">密码</label>
<input class="mdui-textfield-input" type="password" name="password" required/>
<div class="mdui-textfield-error">密码不能为空</div>
</div>
<div class="mdui-panel-item-actions">
<button class="mdui-btn mdui-ripple" mdui-panel-item-close>取消</button>
<button class="mdui-btn mdui-ripple">确定</button>
</div>
</div>
</form>
</div>  
</div>
</div>
</div>
</div>
</div>
</div>

<div class="mdui-card" style="display: inline-block;width:48%; height: 25%">
<div class="mdui-card-media">
<img src="./images/3.jpg"/>
<div class="mdui-card-media-covered">
<div class="mdui-card-primary">
<div class="mdui-panel" mdui-panel style="background:#000; filter:alpha(opacity:30); opacity:0.5">
<div class="mdui-panel-item">
<div class="mdui-panel-item-header">
<div class="mdui-panel-item-title">修改密码</div>
<i class="mdui-panel-item-arrow mdui-icon material-icons">+</i>
</div>
<div class="mdui-panel-item-body">
<form action="update_cgi" method="post">
<div class="mdui-textfield mdui-textfield-floating-label">
<label class="mdui-textfield-label">账号</label>
<input class="mdui-textfield-input" type="text" name="username" equired/>
<div class="mdui-textfield-error">账号不能为空</div>
</div>
<div class="mdui-textfield mdui-textfield-floating-label">
<label class="mdui-textfield-label">旧密码</label>
<input class="mdui-textfield-input" type="password" name="oldpass" required/>
<div class="mdui-textfield-error">密码不能为空</div>
</div>
<div class="mdui-textfield mdui-textfield-floating-label">
<label class="mdui-textfield-label">新密码</label>
<input class="mdui-textfield-input" type="password" name="newpass" required/>
<div class="mdui-textfield-error">密码不能为空</div>
</div>
<div class="mdui-panel-item-actions">
<button class="mdui-btn mdui-ripple" mdui-panel-item-close>取消</button>
<button class="mdui-btn mdui-ripple">确定</button>
</div>
</form>
</div>
</div>  
</div>
</div>
</div>
</div>
</div>

</div>
</body>
</html>
