{ajax_form id='creategroup' method='post' url='index.php?type=creategroup&amp;f=getSubContent&amp;do=1' callback='form_submit'}
<table>
    <tr>
        <td>Groupname:</td>
        <td><input type="text" name="name" value="" size="30"/></td>
    </tr>
    <tr>
        <td>Description:</td>
        <td><input type="text" name="desc" value="" size="30"/></td>
    </tr>
    <tr>
        <td colspan="2" align="center"><input type="submit" value="create"/></td>
    </tr>
</table>
{/ajax_form}
