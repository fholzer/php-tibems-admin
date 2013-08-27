<div>
<b>Consumers:</b><br/>
</div>
<table>
	<tr>
		<td></td><td><b>Id</b></td><td><b>Conn</b></td><td><b>User</b></td><td><b>T</b></td><td><b>Queue</b></td><td><b>SAS</b></td><td><b>Msgs Sent</b></td><td><b>Sent Size</b></td><td><b>Uptime</b></td>
	</tr>
	{foreach from=$data item="entry"}
	<tr>
		<td><img src="images/consumers.png" alt=""/></td><td>{$entry->getCid()}</td><td>{$entry->getConnID()}</td><td>{$entry->getUn()}</td><td>Q</td><td>{$entry->getDn()}</td><td></td><td>{$entry->getMct()}</td><td>{$entry->getMsz()}</td><td>{$entry->getUptime()}</td>
	</tr>
	{foreachelse}
	<tr>
		<td></td><td>no data</td>
	</tr>
	{/foreach}
</table>
