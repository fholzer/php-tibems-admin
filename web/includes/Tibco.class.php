<?php

class Tibco
{
	private $serverurl;
	private $adminname;
	private $adminpass;
	private $connected = false;

	private $serverinfo;
	private $queues;
	private $topics;
	private $durables;
	private $users;
	private $groups;
	private $bridges;
	private $factories;
	private $connections;
	private $consumers;
	private $producers;
	private $transactions;
	private $routes;
	private $jndinames;

	function __construct($serverurl, $adminname, $adminpass)
	{
		$this->serverurl = $serverurl;
		$this->adminname = $adminname;
		$this->adminpass = $adminpass;
	}
	
	function __destruct()
	{
		if($this->connected)
			tibcoadm_disconnect();
	}
	
	public function connect()
	{
		if(strlen($this->serverurl) > 1 && strlen($this->adminname) > 1)
		{
			if(tibcoadm_connect($this->serverurl, $this->adminname, $this->adminpass))
			{
				$this->connected = true;
				return true;
			}else{
				return false;
			}
		}else{
			return false;
		}
	}

	public function disconnect()
	{
		if($this->connected)
			tibcoadm_disconnect();
		$this->connected = false;
	}

	public function getStatus()
	{
		if(!is_object($this->serverinfo))
		{
			$this->serverinfo = new TibcoStatus();
		}
		return $this->serverinfo;
	}

	public function getPermissions($user)
	{
		return new TibcoPermissions($user);
	}

	public function getAcls()
	{
		return tibcoadm_getacls();
	}

	public function getRoutes()
	{
		if(!is_object($this->routes))
		{
			$this->routes = new TibcoRoutes();
		}
		return $this->routes;
	}

	public function getQueues()
	{
		if(!is_object($this->queues))
		{
			$this->queues = new TibcoQueues();
		}
		return $this->queues;
	}

	public function getQueuesStatistics($name)
	{
		return tibcoadm_getqueuesstatistics($name);
	}

	public function createQueue($name, $prefetch=0, $overflow=0, $redelivery=0, $maxbytes=0, $maxmsgs=0, $expiration=0, $flowcontrol=0, $failsafe=false, $secure=false, $isglobal=false, $sname=false, $snameenf=false, $exclusive=false)
	{
		return tibcoadm_createqueue($name, $prefetch, $overflow, $redelivery, $maxbytes, $maxmsgs, $expiration, $flowcontrol, $failsafe, $secure, $isglobal, $sname, $snameenf, $exclusive);
	}

	public function editQueue($name, $prefetch=0, $overflow=0, $redelivery=0, $maxbytes=0, $maxmsgs=0, $expiration=0, $flowcontrol=0, $failsafe=false, $secure=false, $isglobal=false, $sname=false, $snameenf=false, $exclusive=false)
	{
		return tibcoadm_updatequeue($name, $prefetch, $overflow, $redelivery, $maxbytes, $maxmsgs, $expiration, $flowcontrol, $failsafe, $secure, $isglobal, $sname, $snameenf, $exclusive);
	}

	public function purgeQueue($name)
	{
		return tibcoadm_purgequeue($name);
	}

	public function removeQueue($name)
	{
		return tibcoadm_removequeue($name);
	}

	public function createTopic($name, $prefetch=0, $overflow=0, $maxbytes=0, $maxmsgs=0, $expiration=0, $flowcontrol=0, $failsafe=false, $secure=false, $isglobal=false, $sname=false, $snameenf=false)
	{
		return tibcoadm_createtopic($name, $prefetch, $overflow, $maxbytes, $maxmsgs, $expiration, $flowcontrol, $failsafe, $secure, $isglobal, $sname, $snameenf);
	}

	public function editTopic($name, $prefetch=0, $overflow=0, $maxbytes=0, $maxmsgs=0, $expiration=0, $flowcontrol=0, $failsafe=false, $secure=false, $isglobal=false, $sname=false, $snameenf=false)
	{
		return tibcoadm_updatetopic($name, $prefetch, $overflow, $maxbytes, $maxmsgs, $expiration, $flowcontrol, $failsafe, $secure, $isglobal, $sname, $snameenf);
	}

	public function purgeTopic($name)
	{
		return tibcoadm_purgetopic($name);
	}

	public function removeTopic($name)
	{
		return tibcoadm_removetopic($name);
	}

	public function purgeDurable($name, $clientid="")
	{
		return tibcoadm_purgedurable($name, $clientid);
	}

	public function removeDurable($name, $clientid="")
	{
		return tibcoadm_removedurable($name, $clientid);
	}

	public function createDurable($tname, $name, $clientid="")
	{
		return tibcoadm_createdurable($tname, $name, $clientid);
	}

	public function getTopics()
	{
		if(!is_object($this->topics))
		{
			$this->topics = new TibcoTopics();
		}
		return $this->topics;
	}

	public function getDurables()
	{
		if(!is_object($this->durables))
		{
			$this->durables = new TibcoDurables();
		}
		return $this->durables;
	}

	public function getTopicsStatistics($name)
	{
		return tibcoadm_gettopicsstatistics($name);
	}

	public function getConnections()
	{
		if(!is_object($this->connections))
		{
			$this->connections = new TibcoConnections();
		}
		return $this->connections;
	}

	public function getUsers()
	{
		if(!is_object($this->users))
		{
			$this->users = new TibcoUsers();
		}
		return $this->users;
	}

	public function getGroups()
	{
		if(!is_object($this->groups))
		{
			$this->groups = new TibcoGroups();
		}
		return $this->groups;
	}

	public function getGroup($name)
	{
		return TibcoGroups::getGroup($name);
	}

	public function getBridges()
	{
		if(!is_object($this->bridges))
		{
			$this->bridges = new TibcoBridges();
		}
		return $this->bridges;
	}

	public function getFactories()
	{
		if(!is_object($this->factories))
		{
			$this->factories = new TibcoFactories();
		}
		return $this->factories;
	}

	public function getConsumers()
	{
		if(!is_object($this->consumers))
		{
			$this->consumers = new TibcoConsumers();
		}
		return $this->consumers;
	}

	public function getProducers()
	{
		if(!is_object($this->producers))
		{
			$this->producers = new TibcoProducers();
		}
		return $this->producers;
	}

	public function getTransactions()
	{
		if(!is_object($this->transactions))
		{
			$this->transactions = new TibcoTransactions();
		}
		return $this->transactions;
	}

	public function commitTransaction($transId)
	{
		return tibcoadm_commitTransaction($transId);
	}

	public function rollbackTransaction($transId)
	{
		return tibcoadm_rollbackTransaction($transId);
	}

	public function getJndiNames()
	{
		if(!is_object($this->jndinames))
		{
			$this->jndinames = new TibcoJndiNames();
		}
		return $this->jndinames;
	}

	public function createUser($name, $password, $desc="")
	{
		return tibcoadm_createuser($name, $password, $desc);
	}

	public function editUser($name, $password, $desc="")
	{
		return tibcoadm_edituser($name, $password, $desc);
	}

	public function removeUser($name)
	{
		return tibcoadm_removeuser($name);
	}

	public function createGroup($name, $desc="")
	{
		return tibcoadm_creategroup($name, $desc);
	}

	public function removeMember($group, $name)
	{
		return tibcoadm_removemember($group, $name);
	}

	public function addMember($group, $name)
	{
		return tibcoadm_addmember($group, $name);
	}

	public function removeGroup($name)
	{
		return tibcoadm_removegroup($name);
	}

	public function removeConnection($id)
	{
		return tibcoadm_removeconnection($id);
	}

	public function getQueue($name)
	{
		return TibcoQueues::getQueue($name);
	}

	public function getTopic($name)
	{
		return TibcoTopics::getTopic($name);
	}

	public function getBridge($src, $srctype)
	{
		return TibcoBridges::getBridge($src, $srctype);
	}

	public function createBridge($src, $srctype, $dst, $dsttype, $sel="")
	{
		return tibcoadm_createbridge($src, $srctype, $dst, $dsttype, $sel);
	}

	public function removeBridge($src, $srctype, $dst, $dsttype)
	{
		return tibcoadm_removebridge($src, $srctype, $dst, $dsttype);
	}
}
?>