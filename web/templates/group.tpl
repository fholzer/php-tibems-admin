<div>
<b>Group {$name}:</b><br/>
</div>
<table>
	<tr>
		<td></td><td><b>Username</b></td><td><b>Description</b></td><td></td>
	</tr>
	{foreach from=$data item="entry"}
	<tr>
		<td><img src="images/users.png" alt=""/></td><td>{$entry.name}</td><td>{$entry.desc}</td><td><a href="#" onclick="{ajax_update update_id='content' function='getSubContent' params="type=delmember&amp;group=`$name`&amp;name=`$entry.name`"}"><img src="images/del.png" alt="delete"/></a></td>
	</tr>
	{foreachelse}
	<tr>
		<td></td><td colspan="4">no members</td>
	</tr>
	{/foreach}
</table>
<div id='subcontent'><a href="#" onclick="{ajax_update update_id='subcontent' function='getSubContent' params="type=addmember&amp;group=`$name`"}">add Member</a></div>