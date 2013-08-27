<div>
<b>Permissions for user {$name}:</b><br/>
</div>
<table>
	<tr>
		<td></td><td><b>Target</b></td><td><b>Permission</b></td><td></td>
	</tr>
	{foreach from=$data item="entry"}
	<tr>
		<td><img src="images/permissions.png" alt=""/></td><td>{$entry->getTargetType()}={$entry->getTargetName()}</td><td>{$entry->getPermissions()}</td><td><img src="images/del.png" alt="delete"/></td>
	</tr>
	{foreachelse}
	<tr>
		<td></td><td colspan="3">no permissions</td>
	</tr>
	{/foreach}
</table>
