<div>
<b>Connections:</b><br/>
</div>
<table>
	<tr>
		<td></td><td><b>L</b></td><td><b>ID</b></td><td><b>FSXT</b></td><td><b>S</b></td><td><b>Host</b></td><td><b>User</b></td><td><b>IP</b></td><td><b>ClientID</b></td><td><b>Sess</b></td><td><b>Uptime</b></td><td></td>
	</tr>
	{foreach from=$data item="entry"}
	{assign var=connid value=$entry->getConnID()}
	<tr>
		<td><img src="images/connections.png" alt=""/></td><td>{$entry->getCltype()}</td><td>{$entry->getConnID()}</td><td>{$entry->getFlags()}</td><td>{if $entry->isStarted()}+{else}-{/if}</td><td>{$entry->getHost()}</td><td>{$entry->getIpaddr()}</td><td>{$entry->getUserName()}</td><td>{$entry->getClientID()}</td><td>{$entry->getCs()}</td><td>{$entry->getUptime()}</td><td><a href="#" onclick="{ajax_update update_id='content' function='getSubContent' params="type=delconnection&amp;connid=`$connid`"}"><img src="images/del.png" alt="delete"/></a></td>
	</tr>
	{foreachelse}
	<tr>
		<td></td><td colspan="11">no connections</td>
	</tr>
	{/foreach}
</table>
