<div>
<b>Groups:</b><br/>
</div>
<table>
	<tr>
		<td></td><td><b>Group Name</b></td><td><b>Users</b></td><td><b>Desc</b></td><td></td>
	</tr>
	{foreach from=$data item="entry"}
	{assign var=name value=$entry->getName()}
	<tr>
		<td><img src="images/groups.png" alt=""/></td><td><a href="#" onclick="{ajax_update update_id='content' function='getContent' params="type=group&amp;name=`$name`"}">{$entry->getName()}</a></td><td>{$entry->getUserCount()}</td><td>{$entry->getDesc()}</td><td><a href="#" onclick="{ajax_update update_id='content' function='getSubContent' params="type=delgroup&amp;name=`$name`"}"><img src="images/del.png" alt="delete"/></a></td>
	</tr>
	{foreachelse}
	<tr>
		<td></td><td colspan="4">no groups</td>
	</tr>
	{/foreach}
</table>
<div id='subcontent'><a href="#" onclick="{ajax_update update_id='subcontent' function='getSubContent' params='type=creategroup'}">create Group</a></div>
