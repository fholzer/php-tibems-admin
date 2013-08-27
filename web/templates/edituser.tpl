{ajax_form id='edituser' method='post' url="index.php?type=edituser&amp;name=`$name`&amp;f=getSubContent&amp;do=1" callback='form_submit'}
<table>
    <tr>
        <td colspan="2"><b>Edit User {$name}:</b></td>
    </tr>
    <tr>
        <td>Password:</td>
        <td><input type="password" name="password" value="" size="30"/></td>
    </tr>
    <tr>
        <td>Description:</td>
        <td><input type="text" name="desc" value="{$desc}" size="30"/></td>
    </tr>
    <tr>
        <td colspan="2" align="center"><input type="submit" value="save"/></td>
    </tr>
</table>
{/ajax_form}
