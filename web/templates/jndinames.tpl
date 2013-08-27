<div>
<b>JNDI Names:</b><br/>
</div>
<table>
	<tr>
		<td></td><td><b>JNDI Name</b></td><td><b>Type</b></td><td><b>Object Info</b></td>
	</tr>
	{foreach from=$data item="entry"}
	<tr>
		<td><img src="images/jndinames.png" alt=""/></td><td>{$entry->getAlias()}</td><td>{$entry->getJndiType()}</td><td>{$entry->getObjInfo()}</td>
	</tr>
	{foreachelse}
	<tr>
		<td></td><td colspan="3">no queues</td>
	</tr>
	{/foreach}
</table>
