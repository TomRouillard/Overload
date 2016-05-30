
if (window.ENV == "TEST") {
    function getRandChampID() {
        var key = String(Math.floor(Math.random() * 600) + 1);
        if ( ! (key in champions) ) {
            key = getRandChampID();
        }
        return key;
    }
    function getRandIconID() {
        var key = String(Math.floor(Math.random() * 800) + 1);
        if ( ! (key in summonerIcons) ) {
            key = getRandIconID();
        }
        return key;
    }
    function getRandInfos() {
        var leagues  = ['unranked', 'bronze', 'silver', 'gold', 'platinum', 'diamond', 'master', 'challenger' ];
        var rand = parseInt(Math.random() * leagues.length);
        var divisionRand = parseInt(Math.random() * 4 + 1) ;
        var divisions = ['i', 'ii', 'iii', 'iv', 'v']
        var division = rand > 0 && rand < 6  ? divisions[divisionRand] : '' ;
        var infos = {
            tier : leagues[rand],
            entries : [
                {
                    division: division,
                    losses: parseInt(Math.random() * 1000),
                    wins: parseInt(Math.random() * 1000)
                }
            ]
        };
        console.log(infos);
        return infos;
    }
    var respTest = {"gameId":2098462209,"mapId":11,"gameMode":"CLASSIC","gameType":"MATCHED_GAME","gameQueueConfigId":4,"participants":[
    {"teamId":100,"spell1Id":14,"spell2Id":4,"championId": getRandChampID(),"profileIconId":getRandIconID(), "infos": getRandInfos(), "summonerName":"Sidesprang","bot":false,"summonerId":22338565},
    {"teamId":100,"spell1Id":4,"spell2Id":11,"championId": getRandChampID(),"profileIconId":getRandIconID(),"infos": getRandInfos(), "summonerName":"KingWorsa","bot":false,"summonerId":34857282},
    {"teamId":100,"spell1Id":7,"spell2Id":4,"championId": getRandChampID(),"profileIconId":getRandIconID(),"infos": getRandInfos(), "summonerName":"Enton","bot":false,"summonerId":39484945},
    {"teamId":100,"spell1Id":12,"spell2Id":4,"championId": getRandChampID(),"profileIconId":getRandIconID(),"infos": getRandInfos(), "summonerName":"Bones to Papayas","bot":false,"summonerId":43672112},
    {"teamId":100,"spell1Id":7,"spell2Id":4,"championId": getRandChampID(),"profileIconId":getRandIconID(),"infos": getRandInfos(), "summonerName":"Wild Porygon","bot":false,"summonerId":41527558},
    {"teamId":200,"spell1Id":4,"spell2Id":11,"championId": getRandChampID(),"profileIconId":getRandIconID(),"infos": getRandInfos(), "summonerName":"The Wang Carry","bot":false,"summonerId":24560332},
    {"teamId":200,"spell1Id":7,"spell2Id":4,"championId": getRandChampID(),"profileIconId":getRandIconID(),"infos": getRandInfos(), "summonerName":"Fungar","bot":false,"summonerId":25595670},
    {"teamId":200,"spell1Id":14,"spell2Id":4,"championId": getRandChampID(),"profileIconId":getRandIconID(),"infos": getRandInfos(), "summonerName":"yung baloo","bot":false,"summonerId":22025113},
    {"teamId":200,"spell1Id":4,"spell2Id":3,"championId": getRandChampID(),"profileIconId":getRandIconID(),"infos": getRandInfos(), "summonerName":"Alamolo","bot":false,"summonerId":19402186},
    {"teamId":200,"spell1Id":4,"spell2Id":12,"championId": getRandChampID(),"profileIconId":getRandIconID(),"infos": getRandInfos(), "summonerName":"DG Basko","bot":false,"summonerId":22385395}]}
        // var champions = ['Nami', 'Draven', 'Forecast_Janna', 'Pulsefire_Ezreal', 'Aatrox']

    getSynchronizedVariant = function(variable) {
        var result = {
            "imageDirectory": window.currentDir + "images/champions/",
            "gameInfo": JSON.stringify(respTest)
        };

        return result[variable];
    }
}
if (window.ENV == "TEST VIDEO") {
    function getRandChampID() {
        var videos = ['126', '254', '222', '421', '143', '154', '150', '201', '107', '412', '429', '117', '119', '110', '432', '245', '429', '127', '121', '120', '238', '134', '133', '267', '268', '60', '131', '266', '202', '81', '78', '14', '44', '429', '223', '136', '163']
        var key = String(parseInt((Math.random() * (videos.length -1)) )+ 1);
        return videos[key];
    }
    function getRandIconID() {
        var key = String(Math.floor(Math.random() * 800) + 1);
        if ( ! (key in summonerIcons) ) {
            key = getRandIconID();
        }
        return key;
    }
    function getRandInfos() {
        var leagues  = ['unranked', 'bronze', 'silver', 'gold', 'platinum', 'diamond', 'master', 'challenger' ];
        var rand = parseInt(Math.random() * leagues.length);
        var divisionRand = parseInt(Math.random() * 4 + 1) ;
        var divisions = ['i', 'ii', 'iii', 'iv', 'v']
        var division = rand > 0 && rand < 6  ? divisions[divisionRand] : '' ;
        var infos = {
            tier : leagues[rand],
            entries : [
                {
                    division: division,
                    losses: parseInt(Math.random() * 1000),
                    wins: parseInt(Math.random() * 1000)
                }
            ]
        };
        console.log(infos);
        return infos;
    }
    var respTest = {"gameId":2098462209,"mapId":11,"gameMode":"CLASSIC","gameType":"MATCHED_GAME","gameQueueConfigId":4,"participants":[
    {"teamId":100,"spell1Id":14,"spell2Id":4,"championId": getRandChampID(),"profileIconId":getRandIconID(), "infos": getRandInfos(), "summonerName":"Sidesprang","bot":false,"summonerId":22338565},
    {"teamId":100,"spell1Id":4,"spell2Id":11,"championId": getRandChampID(),"profileIconId":getRandIconID(),"infos": getRandInfos(), "summonerName":"KingWorsa","bot":false,"summonerId":34857282},
    {"teamId":100,"spell1Id":7,"spell2Id":4,"championId": getRandChampID(),"profileIconId":getRandIconID(),"infos": getRandInfos(), "summonerName":"Enton","bot":false,"summonerId":39484945},
    {"teamId":100,"spell1Id":12,"spell2Id":4,"championId": getRandChampID(),"profileIconId":getRandIconID(),"infos": getRandInfos(), "summonerName":"Bones to Papayas","bot":false,"summonerId":43672112},
    {"teamId":100,"spell1Id":7,"spell2Id":4,"championId": getRandChampID(),"profileIconId":getRandIconID(),"infos": getRandInfos(), "summonerName":"Wild Porygon","bot":false,"summonerId":41527558},
    {"teamId":200,"spell1Id":4,"spell2Id":11,"championId": getRandChampID(),"profileIconId":getRandIconID(),"infos": getRandInfos(), "summonerName":"The Wang Carry","bot":false,"summonerId":24560332},
    {"teamId":200,"spell1Id":7,"spell2Id":4,"championId": getRandChampID(),"profileIconId":getRandIconID(),"infos": getRandInfos(), "summonerName":"Fungar","bot":false,"summonerId":25595670},
    {"teamId":200,"spell1Id":14,"spell2Id":4,"championId": getRandChampID(),"profileIconId":getRandIconID(),"infos": getRandInfos(), "summonerName":"yung baloo","bot":false,"summonerId":22025113},
    {"teamId":200,"spell1Id":4,"spell2Id":3,"championId": getRandChampID(),"profileIconId":getRandIconID(),"infos": getRandInfos(), "summonerName":"Alamolo","bot":false,"summonerId":19402186},
    {"teamId":200,"spell1Id":4,"spell2Id":12,"championId": getRandChampID(),"profileIconId":getRandIconID(),"infos": getRandInfos(), "summonerName":"DG Basko","bot":false,"summonerId":22385395}]}
        // var champions = ['Nami', 'Draven', 'Forecast_Janna', 'Pulsefire_Ezreal', 'Aatrox']

    getSynchronizedVariant = function(variable) {
        var result = {
            "imageDirectory": window.currentDir + "images/champions/",
            "gameInfo": JSON.stringify(respTest)
        };

        return result[variable];
    }
}