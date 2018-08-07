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
