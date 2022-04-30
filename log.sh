#!/bin/bash

# NOTE: I want to avoid storing my password on github, so put the base64 encoded key in the file auth.txt.
AUTH=$(<auth.txt)
#AUTH=${AUTH//$'\r'/}

rm dump.txt

for (( n=1; n<=100; n++ ))
do
	curl 'http://psb19526.seedbox.io/rutorrent/plugins/httprpc/action.php' -X POST -H "Authorization: Basic $AUTH" --data-raw 'mode=list&cmd=d.throttle_name%3D&cmd=d.custom%3Dchk-state&cmd=d.custom%3Dchk-time&cmd=d.custom%3Dsch_ignore&cmd=cat%3D%22%24t.multicall%3Dd.hash%3D%2Ct.scrape_complete%3D%2Ccat%3D%7B%23%7D%22&cmd=cat%3D%22%24t.multicall%3Dd.hash%3D%2Ct.scrape_incomplete%3D%2Ccat%3D%7B%23%7D%22&cmd=d.custom%3Dx-pushbullet&cmd=cat%3D%24d.views%3D&cmd=d.custom%3Dseedingtime&cmd=d.custom%3Daddtime' >> dump.txt
	echo $'\n' >> dump.txt
	sleep 300
done
