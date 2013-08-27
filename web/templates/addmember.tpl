{ajax_form id='addmember' method='post' url="index.php?type=addmember&amp;group=`$group`&amp;f=getSubContent&amp;do=1" callback='form_submit'}
<table>
    <tr>
        <td>Username:</td>
        <td><select name="name">
        {foreach from=$users item="entry"}
        <option value="{$entry->getName()}">{$entry->getName()}</option>
        {/foreach}
        </select></td>
    </tr>
    <tr>
        <td colspan="2" align="center"><input type="submit" value="add"/></td>
    </tr>
</table>
{/ajax_form}
