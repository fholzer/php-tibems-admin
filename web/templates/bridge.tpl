<div>
<b>Bridge {$src.dn}:</b><br/>
</div>
<table>
	<tr>
		<td></td><td><b>Target Name</b></td><td><b>Type</b></td><td><b>Selector</b></td><td></td>
	</tr>
	{foreach from=$data item="entry"}
	<tr>
		<td>{if $entry.dt==1}<img src="images/queues.png" alt=""/>{elseif $entry.dt==2}<img src="images/topics.png" alt=""/>{/if}</td><td>{$entry.dn}</td><td>{if $entry.dt==1}Q{elseif $entry.dt==2}T{/if}</td><td></td><td><a href="#" onclick="{ajax_update update_id='content' function='getSubContent' params="type=delbridge&amp;src=`$src.dn`&amp;srctype=`$src.dt`&amp;dst=`$entry.dn`&amp;dsttype=`$entry.dt`"}"><img src="images/del.png" alt="delete"/></a></td>
	</tr>
	{foreachelse}
	<tr>
		<td></td><td colspan="5">no bridge</td>
	</tr>
	{/foreach}
</table>
