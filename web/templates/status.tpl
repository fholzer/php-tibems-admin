<div>
<b>Serverstatus:</b><br/>
</div>
<table>
	<tr>
		<td>Servername:</td><td>{$Serverstatus->getServer()}</td>
	</tr>
	<tr>
		<td>State:</td><td>{$Serverstatus->getState()}</td>
	</tr>
	<tr>
		<td>Version:</td><td>{$Serverstatus->getVersion()}</td>
	</tr>
	<tr>
		<td>Listen:</td><td>{$Serverstatus->GetListen()}</td>
	</tr>
	<tr>
		<td>Queues:</td><td>{$Serverstatus->getQueuenum()} ({$Serverstatus->getDynqueuenum()} dynamic, {$Serverstatus->getTmpqueuenum()} temporary)</td>
	</tr>
	<tr>
		<td>Topics:</td><td>{$Serverstatus->getTopicnum()} ({$Serverstatus->getDyntopicnum()} dynamic, {$Serverstatus->getTmptopicnum()} temporary)</td>
	</tr>
	<tr>
		<td>Connections:</td><td>{$Serverstatus->getConnnum()} (max {$Serverstatus->getMaxconns()})</td>
	</tr>
	<tr>
		<td>Sessions:</td><td>{$Serverstatus->getSessnum()}</td>
	</tr>
	<tr>
		<td>Producers:</td><td>{$Serverstatus->getProdnum()}</td>
	</tr>
	<tr>
		<td>Consumers:</td><td>{$Serverstatus->getConsnum()}</td>
	</tr>
	<tr>
		<td>Durables:</td><td>{$Serverstatus->getDurablenum()}</td>
	</tr>
	<tr>
		<td>Pending Messages:</td><td>{$Serverstatus->getPendcount()}</td>
	</tr>
	<tr>
		<td>Pending Message Size:</td><td>{$Serverstatus->getPendsize()}</td>
	</tr>
	<tr>
		<td>Incoming Msg/Sec:</td><td>{$Serverstatus->getInrm()}</td>
	</tr>
	<tr>
		<td>Outgoing Msg/Sec:</td><td>{$Serverstatus->getOutrm()}</td>
	</tr>
	<tr>
		<td>In MessageCount:</td><td>{$Serverstatus->getInmct()}</td>
	</tr>
	<tr>
		<td>Out MessageCount:</td><td>{$Serverstatus->getOutmct()}</td>
	</tr>
	<tr>
		<td>Uptime:</td><td>{$Serverstatus->getUptime()}</td>
	</tr>
</table>
