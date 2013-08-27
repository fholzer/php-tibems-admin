<div>
<b>Transactions:</b><br/>
</div>
<table>
	<tr>
		<td></td><td><b>State</b></td><td><b>Format ID</b></td><td><b>GTrid Len</b></td><td><b>Bqual Len</b></td><td><b>Data</b></td><td></td>
	</tr>
	{foreach from=$data item="entry"}
	{assign var=name value=$entry->getBytes()}
	<tr>
		<td><img src="images/transactions.png" alt=""/></td><td>{$entry->getState()}</td><td>{$entry->getFormatId()}</td><td>{$entry->getGrId()}</td><td>{$entry->getBranchQualLength()}</td><td>{$entry->getGlobalTxId()}{$entry->getBranchQual()}</td><td><a href="#" onclick="{ajax_update update_id='content' function='getSubContent' params="type=committransaction&amp;name=`$name`"}"><img src="images/commit.png" alt="edit"/></a> <a href="#" onclick="{ajax_update update_id='content' function='getSubContent' params="type=rollbacktransaction&amp;name=`$name`"}"><img src="images/rollback.png" alt="rollback"/></a></td>
	</tr>
	{foreachelse}
	<tr>
		<td></td><td colspan="6">no data</td>
	</tr>
	{/foreach}
</table>
