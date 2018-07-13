package ch.bildspur.silva.network

import ch.bildspur.silva.Sketch
import ch.bildspur.silva.model.TreeInformation
import oscP5.OscMessage
import java.time.LocalDateTime
import kotlin.concurrent.thread

class TreeConnection(val sketch : Sketch,
                     val osc : OscController) {

    val treeInfo = TreeInformation()

    @Volatile var isRunning = false

    @Volatile private var recordMessages = false
    val messageBuffer = mutableListOf<OscMessage>()

    init {
        osc.onOscMessage += {
            if(recordMessages)
                messageBuffer.add(it)

            updateTreeInformation(it)
        }
    }

    fun updateTreeInformation(msg : OscMessage)
    {
        when (msg.addrPattern()) {
            "/silva/scene/active" -> {
                treeInfo.activeScene = msg.arguments()[0] as String
                treeInfo.lastHeartBeat = LocalDateTime.now()
            }

            "/silva/debug/hic" -> treeInfo.hic = msg.arguments()[0] as Float
            "/silva/debug/life" -> treeInfo.life = msg.arguments()[0] as Float
            "/silva/debug/lux" -> treeInfo.lux = msg.arguments()[0] as Float
            "/silva/debug/threshold" -> treeInfo.threshold = msg.arguments()[0] as Float
        }
    }

    fun readDataFromTree() {
        // not implemented
    }

    fun writeDataToTree() {
        isRunning = true
        thread {
            println("writing data to tree...")
            sketch.appConfig.leafs.forEach { leaf ->
                println("updating ${leaf.index} with distance ${leaf.distance}...")
                leaf.selected = true
                osc.sendMessage("/silva/update", leaf.index.toFloat(), leaf.distance.toFloat())
                Thread.sleep(500)
                leaf.selected = false
            }

            Thread.sleep(1000)
            saveTree()

            Thread.sleep(1000)
            println("done!")
            isRunning = false
        }
    }

    fun saveTree()
    {
        println("saving configuration...")
        osc.sendMessage("/silva/save", 0f)
    }
}