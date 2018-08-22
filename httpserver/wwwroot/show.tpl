<html>
<head>
<meta charset="utf-8">
<link rel="stylesheet" href="css/mdui.min.css">
<script src="js/mdui.min.js"></script>
<title>{{USERNAME}}的主页</title>
</head>
<body >
<div class="mdui-panel mdui-panel-popout" mdui-panel>

  <div class="mdui-panel-item" id="card1"> 
    <div class="mdui-panel-item-header">
    <div class="mdui-panel-item-title">个人简历</div>
    <i class="mdui-panel-item-arrow mdui-icon material-icons">keyboard_arrow_down</i>
    </div>
    <div class="mdui-panel-item-body">
    <embed width="800" height="600" src="{{FILEURL}}"></embed>        
    </div>
  </div>
  
  <div class="mdui-panel-item" id="card2">
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
        </thead>
        {{#NOTES}}
        <tbody>
        <tr>
            <td>{{value1}}</td>
            <td><a href="{{value2}}">{{value2}}</a></td>
            <td>{{value3}}</td>
            <td>{{value4}}</td>
        </tr>
        </tbody>
        {{/NOTES}}
        </table>
        </div>
    </div>
  </div>
   
  <div class="mdui-panel-item" id="card3">
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

        </div>
    </div>
</div>
</body>
</html>
