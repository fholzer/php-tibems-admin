<div>
<b>Durables:</b><br/>
</div>
<table>
	<tr>
		<td></td><td><b>Topic Name</b></td><td><b>Durable</b></td><td><b>User</b></td><td><b>Msgs</b></td><td><b>Size</b></td><td></td>
	</tr>
	{foreach from=$data item="entry"}
	{assign var=name value=$entry->getName()}
	<tr>
		<td><img src="images/durables.png" alt=""/></td><td>{$entry->getTn()}</td><td>{$entry->getName()}</td><td>{if $entry->isOnline()}{$entry->getClientID()}{else}&lt;offline&gt;{/if}</td><td>{$entry->getNm()}</td><td>{$entry->getPs()}</td><td><a href="#" onclick="{ajax_update update_id='content' function='getSubContent' params="type=purgedurable&amp;name=`$name`"}"><img src="images/purge.png" alt="purge"/></a> <a href="#" onclick="{ajax_update update_id='content' function='getSubContent' params="type=deldurable&amp;name=`$name`"}"><img src="images/del.png" alt="delete"/></a></td>
	</tr>
	{foreachelse}
	<tr>
		<td></td><td colspan="5">no durables</td>
	</tr>
	{/foreach}
</table>
<div id='subcontent'><a href="#" onclick="{ajax_update update_id='subcontent' function='getSubContent' params='type=createdurable'}">create Durable</a></div>
