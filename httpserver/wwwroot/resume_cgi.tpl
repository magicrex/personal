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
  
