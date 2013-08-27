<div>
<b>Producers:</b><br/>
</div>
<table>
	<tr>
		<td></td><td><b>Id</b></td><td><b>Conn</b></td><td><b>User</b></td><td><b>T</b></td><td><b>Queue</b></td><td><b>SAS</b></td><td><b>Msgs Sent</b></td><td><b>Sent Size</b></td>
	</tr>
	{foreach from=$data item="entry"}
	<tr>
		<td><img src="images/producers.png" alt=""/></td><td>{$entry->getPid()}</td><td>{$entry->getConnID()}</td><td>{$entry->getUn()}</td><td>Q</td><td>{$entry->getDn()}</td><td></td><td>{$entry->getMct()}</td><td>{$entry->getMsz()}</td>
	</tr>
	{foreachelse}
	<tr>
		<td></td><td>no data</td>
	</tr>
	{/foreach}
</table>
