<div>
<b>Routes:</b><br/>
</div>
<table>
	<tr>
		<td></td><td><b>Route</b></td><td><b>T</b></td><td><b>ConnID</b></td><td><b>Url</b></td><td><b>ZoneName</b></td><td><b>ZoneType</b></td>
	</tr>
	{foreach from=$data item="entry"}
	<tr>
		<td><img src="images/routes.png" alt=""/></td><td>{$entry->getName()}</td><td></td><td>{$entry->getConnID()}</td><td>{$entry->getUrl()}</td><td>{$entry->getZoneName()}</td><td>{$entry->getZoneTypeString()}</td>
	</tr>
	{foreachelse}
	<tr>
		<td></td><td colspan="6">no routes</td>
	</tr>
	{/foreach}
</table>
