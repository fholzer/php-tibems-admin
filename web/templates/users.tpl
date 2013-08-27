<div>
<b>Users:</b><br/>
</div>
<table>
	<tr>
		<td></td><td><b>Name</b></td><td><b>Desc</b></td><td></td>
	</tr>
	{foreach from=$data item="entry"}
	{assign var=name value=$entry->getName()}
	{assign var=desc value=$entry->getDesc()}
	<tr>
		<td><img src="images/users.png" alt=""/></td><td>{$name}</td><td>{$desc}</td><td><a href="#" onclick="{ajax_update update_id='subcontent' function='getSubContent' params="type=edituser&amp;name=`$name`&amp;desc=`$desc`"}"><img src="images/edit.png" alt="edit"/></a> <a href="#" onclick="{ajax_update update_id='content' function='getContent' params="type=permuser&amp;name=`$name`"}"><img src="images/permissions.png" alt="permissions"/></a> <a href="#" onclick="{ajax_update update_id='content' function='getSubContent' params="type=deluser&amp;name=`$name`"}"><img src="images/del.png" alt="delete"/></a></td>
	</tr>
	{foreachelse}
	<tr>
		<td></td><td colspan="3">no users</td>
	</tr>
	{/foreach}
</table>
<div id='subcontent'><a href="#" onclick="{ajax_update update_id='subcontent' function='getSubContent' params='type=createuser'}">create User</a></div>
