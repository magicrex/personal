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
        <lable style="font-weight: 400">添加一个链接:{{ADDNOTE}}</lable>
        <div class="mdui-textfield">
              <label id="mess21" class="mdui-textfield-label">标题</label>
                <textarea Class="mdui-textfield-input"></textarea>
        </div>
        <div class="mdui-textfield">
              <label id="mess22" class="mdui-textfield-label">简介</label>
                <textarea class="mdui-textfield-input"></textarea>
        </div>
        <div class="mdui-textfield">
              <label id="mess23" class="mdui-textfield-label">分类</label>
                <textarea class="mdui-textfield-input"></textarea>
        </div>
        <div class="mdui-textfield">
              <label id="mess24" class="mdui-textfield-label">链接</label>
                <textarea class="mdui-textfield-input"></textarea>
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
