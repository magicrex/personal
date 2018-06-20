<!--ctexample.tpl-->
<html>
    <head>
        <title>{{NAME}}</title>
    </head>
    <body>
        Hello{{NAME}},
        You have just won ${{VALUE}}!
        <table>
            {{#IN_TABLE}}
            <tr>
                <td>{{ITEM}}</td>
                <td>{{TAXED_VALUE}}</td>
            </tr>
            {{/IN_TABLE}}
        </table>
        {{>INCLUDE_TEMPLATE}}

    </body>
</html>
