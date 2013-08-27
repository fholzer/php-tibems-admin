<div>
<b>Topics:</b><br/>
</div>
<table>
	<tr>
		<td></td><td><b>Name</b></td><td><b>SNFGEIBCT</b></td><td><b>Subs</b></td><td><b>Durcs</b></td><td><b>Msgs</b></td><td><b>Size</b></td><td></td>
	</tr>
	{foreach from=$data item="entry"}
	{assign var=name value=$entry->getDn()}
	<tr>
		<td><img src="images/topics.png" alt=""/></td><td>{if !$entry->isStatic()}* {/if}{$entry->getDn()}</td><td>{$entry->getProps()}</td><td>{$entry->getCc()}</td><td>{$entry->getCd()}</td><td>{$entry->getNm()}</td><td>{$entry->getPs()}</td><td><a href="#" onclick="{ajax_update update_id='content' function='getSubContent' params="type=purgetopic&amp;name=`$name`"}"><img src="images/purge.png" alt="purge"/></a> <a href="#" onclick="{ajax_update update_id='subcontent' function='getSubContent' params="type=edittopic&amp;name=`$name`"}"><img src="images/edit.png" alt="edit"/></a> <a href="#" onclick="{ajax_update update_id='content' function='getSubContent' params="type=deltopic&amp;name=`$name`"}"><img src="images/del.png" alt="delete"/></a></td>
	</tr>
	{foreachelse}
	<tr>
		<td></td><td colspan="6">no topics</td>
	</tr>
	{/foreach}
</table>
<div id='subcontent'><a href="#" onclick="{ajax_update update_id='subcontent' function='getSubContent' params='type=createtopic'}">create Topic</a></div>
