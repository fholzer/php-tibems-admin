<div>
<b>Factories:</b><br/>
</div>
<table>
	<tr>
		<td></td><td><b>Factory Type</b></td><td><b>JNDI Name</b></td><td><b>Url</b></td>
	</tr>
	{foreach from=$data item="entry"}
	<tr>
		<td><img src="images/factories.png" alt=""/></td><td>{$entry->getFtype()}</td>
		<td>
		{foreach from=$entry->getAset() item="aset"}
			{$aset}<br/>
		{/foreach}
		</td>
		<td>{$entry->getUrl()}</td>
	</tr>
	{foreachelse}
	<tr>
		<td></td><td colspan="2">no factories</td>
	</tr>
	{/foreach}
</table>
