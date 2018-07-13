package ch.bildspur.silva.network

import ch.bildspur.silva.Sketch
import netP5.NetAddress
import oscP5.OscMessage
import oscP5.OscP5


/**
 * Created by cansik on 09.07.17.
 */
class OscController(internal var sketch: Sketch) {
    @Volatile
    var isSetup = false

    lateinit var apps: NetAddress

    lateinit var osc: OscP5

    fun setup(incomingPort : Int, outgoingPort : Int) {
        osc = OscP5(this, incomingPort)
        apps = NetAddress("255.255.255.255", outgoingPort)

        isSetup = true
    }

    fun stop()
    {
        osc.stop()
    }

    fun oscEvent(msg: OscMessage) {
        when (msg.addrPattern()) {
            "/floje/remote/interaction" -> {

            }
        }
    }

    fun sendMessage(ip: NetAddress, address: String, value: Float) {
        val m = OscMessage(address)
        m.add(value)
        osc.send(m, ip)
    }

    fun sendMessage(address: String, value: Float) {
        val m = OscMessage(address)
        m.add(value)
        osc.send(m, apps)
    }

    fun sendMessage(address: String, value: String) {
        val m = OscMessage(address)
        m.add(value)
        osc.send(m, apps)
    }
}