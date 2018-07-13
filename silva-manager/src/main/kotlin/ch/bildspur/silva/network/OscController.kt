package ch.bildspur.silva.network

import ch.bildspur.silva.Sketch
import ch.bildspur.silva.event.Event
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

    val onOscMessage = Event<OscMessage>()

    fun setup(incomingPort: Int, outgoingPort: Int) {
        osc = OscP5(this, incomingPort)
        apps = NetAddress("255.255.255.255", outgoingPort)

        isSetup = true
    }

    fun stop() {
        osc.stop()
    }

    fun oscEvent(msg: OscMessage) {
        onOscMessage.invoke(msg)
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

    fun sendMessage(address: String, value1: Float, value2: Float) {
        val m = OscMessage(address)
        m.add(value1)
        m.add(value2)
        osc.send(m, apps)
    }

    fun sendMessage(address: String, value: String) {
        val m = OscMessage(address)
        m.add(value)
        osc.send(m, apps)
    }
}