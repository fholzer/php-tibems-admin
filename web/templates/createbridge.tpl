{ajax_form id='createbridge' method='post' url='index.php?type=createbridge&amp;f=getSubContent&amp;do=1' callback='form_submit'}
<table>
    <tr>
        <td>Source:</td>
        <td><select name="srctype"><option value="2">Topic</option><option value="1">Queue</option></select></td>
        <td><input type="text" name="src" value="" size="30"/></td>
    </tr>
    <tr>
        <td>Target:</td>
        <td><select name="dsttype"><option value="1">Queue</option><option value="2">Topic</option></select></td>
        <td><input type="text" name="dst" value="" size="30"/></td>
    </tr>
    <tr>
        <td>Selector:</td>
        <td colspan="2"><input type="text" name="selector" value="" size="30"/></td>
    </tr>
    <tr>
        <td colspan="3" align="center"><input type="submit" value="create"/></td>
    </tr>
</table>
{/ajax_form}
