{include file="header.tpl"}
<div id="menu"><img src="images/logo.png" alt="" /></div>
<div id="content">
<form action="index.php" method="post">
<table>
    {if $error ne ""}
        <tr>
            <td bgcolor="yellow" colspan="2">
                {$error}
            </td>
        </tr>
    {/if}
    <tr>
        <td>Server Url:</td>
        <td><input type="text" name="server" value="{$server|escape}" size="30"/></td>
    </tr>
    <tr>
        <td>Server List:</td>
        <td><select name="serverlist"><option value="0">custom Server</option>
	{foreach from=$data item="entry"}
        <option value="{$entry.url|escape}">{$entry.name}</option>
	{/foreach}
        </select></td>
    </tr>
    <tr>
        <td>Loginname:</td>
        <td><input type="text" name="uname" value="{$uname|escape}" size="20"/></td>
    </tr>
    <tr>
        <td>Password:</td>
        <td><input type="password" name="passwd" value="" size="20"/></td>
    </tr>
    <tr>
        <td colspan="2" align="center"><input type="submit" value="Submit"/></td>
    </tr>
</table>
</form>
</div>
{include file="footer.tpl"}
