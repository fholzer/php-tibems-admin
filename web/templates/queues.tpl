<div>
<b>Queues:</b><br/>
</div>
<table>
	<tr>
		<td></td><td><b>Name</b></td><td><b>SNFGXIBCT</b></td><td><b>Pre</b></td><td><b>Rcvrs</b></td><td><b>Msgs</b></td><td><b>Size</b></td><td></td>
	</tr>
	{foreach from=$data item="entry"}
	{assign var=name value=$entry->getDn()}
	<tr>
		<td><img src="images/queues.png" alt=""/></td><td>{if !$entry->isStatic()}* {/if}{$entry->getDn()}</td><td>{$entry->getProps()}</td><td>{if $entry->getPf() == -1}none {else}{$entry->getPf()}{/if}{if $entry->prefetchInherited()}* {/if}</td><td>{$entry->getCc()}</td><td>{$entry->getNm()}</td><td>{$entry->getPs()}</td><td><a href="#" onclick="{ajax_update update_id='content' function='getSubContent' params="type=purgequeue&amp;name=`$name`"}"><img src="images/purge.png" alt="purge"/></a> <a href="#" onclick="{ajax_update update_id='subcontent' function='getSubContent' params="type=editqueue&amp;name=`$name`"}"><img src="images/edit.png" alt="edit"/></a> <a href="#" onclick="{ajax_update update_id='content' function='getSubContent' params="type=delqueue&amp;name=`$name`"}"><img src="images/del.png" alt="delete"/></a></td>
	</tr>
	{foreachelse}
	<tr>
		<td></td><td colspan="7">no queues</td>
	</tr>
	{/foreach}
</table>
<div id='subcontent'><a href="#" onclick="{ajax_update update_id='subcontent' function='getSubContent' params='type=createqueue'}">create Queue</a></div>
