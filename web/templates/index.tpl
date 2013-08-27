{include file="header.tpl"}
<div id="menu">
<table>
	<tr>
		<td><img src="images/server.png" alt=""/></td><td><a href="#" onclick="{ajax_update update_id='content' function='getContent' params='type=status'}">Serverstatus</a></td>
	</tr><tr>
		<td><img src="images/queues.png" alt=""/></td><td><a href="#" onclick="{ajax_update update_id='content' function='getContent' params='type=queues'}">Queues</a></td>
	</tr><tr>
		<td><img src="images/topics.png" alt=""/></td><td><a href="#" onclick="{ajax_update update_id='content' function='getContent' params='type=topics'}">Topics</a></td>
	</tr><tr>
		<td><img src="images/bridges.png" alt=""/></td><td><a href="#" onclick="{ajax_update update_id='content' function='getContent' params='type=bridges'}">Bridges</a></td>
	</tr><tr>
		<td><img src="images/connections.png" alt=""/></td><td><a href="#" onclick="{ajax_update update_id='content' function='getContent' params='type=connections'}">Connections</a></td>
	</tr><tr>
		<td><img src="images/durables.png" alt=""/></td><td><a href="#" onclick="{ajax_update update_id='content' function='getContent' params='type=durables'}">Durables</a></td>
	</tr><tr>
		<td><img src="images/consumers.png" alt=""/></td><td><a href="#" onclick="{ajax_update update_id='content' function='getContent' params='type=consumers'}">Consumers</a></td>
	</tr><tr>
		<td><img src="images/producers.png" alt=""/></td><td><a href="#" onclick="{ajax_update update_id='content' function='getContent' params='type=producers'}">Producers</a></td>
	</tr><tr>
		<td><img src="images/transactions.png" alt=""/></td><td><a href="#" onclick="{ajax_update update_id='content' function='getContent' params='type=transactions'}">Transactions</a></td>
	</tr><tr>
		<td><img src="images/jndinames.png" alt=""/></td><td><a href="#" onclick="{ajax_update update_id='content' function='getContent' params='type=jndinames'}">JNDI Names</a></td>
	</tr><tr>
		<td><img src="images/users.png" alt=""/></td><td><a href="#" onclick="{ajax_update update_id='content' function='getContent' params='type=users'}">Users</a></td>
	</tr><tr>
		<td><img src="images/groups.png" alt=""/></td><td><a href="#" onclick="{ajax_update update_id='content' function='getContent' params='type=groups'}">Groups</a></td>
	</tr><tr>
		<td><img src="images/factories.png" alt=""/></td><td><a href="#" onclick="{ajax_update update_id='content' function='getContent' params='type=factories'}">Factories</a></td>
	</tr><tr>
		<td><img src="images/routes.png" alt=""/></td><td><a href="#" onclick="{ajax_update update_id='content' function='getContent' params='type=routes'}">Routes</a></td>
	</tr>
</table>
<div id="copy">ver {$version}</div>
</div>
<div id='content'/>
{include file="footer.tpl"}
