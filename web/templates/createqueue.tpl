{ajax_form id='createqueue' method='post' url='index.php?type=createqueue&amp;f=getSubContent&amp;do=1' callback='form_submit'}
<table>
    <tr>
        <td>Queue Name:</td>
        <td><input type="text" name="name" value="" size="30"/></td>
    </tr>
    <tr>
        <td>Prefetch:</td>
        <td><input type="text" name="prefetch" value="0" size="5"/>msgs (-1 = none)</td>
    </tr>
    <tr>
        <td>Overflow Policy:</td>
        <td><select name="overflow"><option value="0">default</option><option value="1">discard Old</option><option value="2">reject Incoming</option></select></td>
    </tr>
    <tr>
        <td>Max Msg Redelivery:</td>
        <td><input type="text" name="redelivery" value="0" size="10"/>2-255 times</td>
    </tr>
    <tr>
        <td>Max Bytes:</td>
        <td><input type="text" name="maxbytes" value="0" size="10"/>bytes</td>
    </tr>
    <tr>
        <td>Max Messages:</td>
        <td><input type="text" name="maxmsgs" value="0" size="10"/>msgs</td>
    </tr>
    <tr>
        <td>Msg Expiration:</td>
        <td><input type="text" name="expiration" value="0" size="10"/>seconds</td>
    </tr>
    <tr>
        <td>Flowcontrol:</td>
        <td><input type="text" name="flowcontrol" value="0" size="10"/>bytes</td>
    </tr>
    <tr>
        <td>Failsafe:</td>
        <td><input type="checkbox" name="failsafe"/></td>
    </tr>
    <tr>
        <td>Secure:</td>
        <td><input type="checkbox" name="secure"/></td>
    </tr>
    <tr>
        <td>Global:</td>
        <td><input type="checkbox" name="isglobal"/></td>
    </tr>
    <tr>
        <td>Senders Name:</td>
        <td><input type="checkbox" name="sname"/></td>
    </tr>
    <tr>
        <td>Senders Name Enforced:</td>
        <td><input type="checkbox" name="snameenf"/></td>
    </tr>
    <tr>
        <td>Exclusive:</td>
        <td><input type="checkbox" name="exclusive"/></td>
    </tr>
    <tr>
        <td colspan="2" align="center"><input type="submit" value="create"/></td>
    </tr>
</table>
{/ajax_form}
