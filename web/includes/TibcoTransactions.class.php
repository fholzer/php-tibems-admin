<?php

class TibcoTransactions
{
	private $transactions;

	function __construct()
	{
		$transactions = tibcoadm_gettransactions();
		$i=0;
		while(is_array($transactions['xid'.$i]))
		{
			$this->transactions[] = new TibcoTransaction($transactions['xid'.$i]);
			$i++;
		}
	}

	public function getAll()
	{
		return $this->transactions;
	}
}

?>