package ch.bildspur.silva.model

import java.time.LocalDateTime

class TreeInformation {
    var lastHeartBeat = LocalDateTime.MIN

    var activeScene = ""

    var hic = -1f

    var life = -1

    var lux = -1

    var threshold = -1
}