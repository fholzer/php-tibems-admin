<div>
<b>Bridges:</b><br/>
</div>
<table>
	<tr>
		<td></td><td></td><td><b>Source Name</b></td><td><b>Queue Targets</b></td><td><b>Topic Targets</b></td><td></td>
	</tr>
	{foreach from=$data item="entry"}
	{assign var=src value=$entry->getDn()}
	{assign var=srctype value=$entry->getDt()}
	<tr>
		<td><img src="images/bridges.png" alt=""/></td><td>{if $entry->getDt()==1}Q{elseif $entry->getDt()==2}T{/if}</td><td><a href="#" onclick="{ajax_update update_id='content' function='getContent' params="type=bridge&amp;src=`$src`&amp;srctype=`$srctype`"}">{$entry->getDn()}</a></td><td>{$entry->getQc()}</td><td>{$entry->getTc()}</td><td></td>
	</tr>
	{foreachelse}
	<tr>
		<td></td><td colspan="5">no bridges</td>
	</tr>
	{/foreach}
</table>
<div id='subcontent'><a href="#" onclick="{ajax_update update_id='subcontent' function='getSubContent' params='type=createbridge'}">create Bridge</a></div>
