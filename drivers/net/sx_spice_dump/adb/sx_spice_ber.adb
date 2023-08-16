<app name="BER">
    <protocol name="eth">

        <indexes>

            <enum_index name="port_type" reg="">
                <index_type name="Network"   value="0" />
                <index_type name="Near_end_point"   value="1" />
                <index_type name="Internal_RC_LR"   value="2" />
                <index_type name="Far_end"   value="3" />
                <index_type name="USR_main"   value="4" />
                <index_type name="USR_tile"   value="5" />
            </enum_index>

            <enum_index name="grp" reg="">
                <index_type name="IEEE_802_3"   value="0x0" />
                <index_type name="RFC_2863"   value="0x1" />
                <index_type name="RFC_2819"   value="0x2" />
                <index_type name="RFC_3635"   value="0x3" />
                <index_type name="Ethernet_Extended"   value="0x5" />
                <index_type name="Ethernet_Discard"   value="0x6" />
                <index_type name="Link_Level_Retransmission"   value="0x8" />
                <index_type name="Per_Priority"   value="0x10" />
                <index_type name="Per_Traffic_Class"   value="0x11" />
                <index_type name="Physical_layer"   value="0x12" />
                <index_type name="Per_Traffic_Class_Congestion"   value="0x13" />
                <index_type name="Per_Receive_Buffer"   value="0x15" />
                <index_type name="Physical_Layer_Statistical"   value="0x16" />
                <index_type name="Out_of_Band_Port"   value="0x19" />
                <index_type name="InfiniBand_Port"   value="0x20" />
                <index_type name="InfiniBand_Extended_Port"   value="0x21" />
                <index_type name="PLR_counters_group"   value="0x22" />
                <index_type name="RS_FEC_Histogram_group"   value="0x23" />
                <index_type name="USR_XSR_Physical_layer_counters_group"   value="0x24" />
                <index_type name="Infiniband_pkts_counters"   value="0x25" />
            </enum_index>

            <enum_index name="page_select" reg="">
                <index_type name="Operational_info_page"         value="0" />
                <index_type name="Troubleshooting_info_page"     value="1" />
                <index_type name="Phy_info_page"                 value="2" />
                <index_type name="Module_info_page"              value="3" />
                <index_type name="Port_events_page"              value="4" />
                <index_type name="Device_events_page"            value="5" />
                <index_type name="Link_down_info"                value="6" />
                <index_type name="Link_down_events"              value="7" />
                <index_type name="Link_up_info"                  value="8" />
                <index_type name="Module_latched_flag_info_page" value="9" />
                <index_type name="link_down_info_ext"            value="10" />
                <index_type name="mng_debug_page"                value="0xFE" />
                <index_type name="phy_debug_page"                value="0XFF" />
            </enum_index>

            <enum_index name="slot_index" reg="">
                <index_type name="Main_board"   value="0" />
            </enum_index>

            <enum_index name="proto_mask" reg="">
                <index_type name="InfiniBand"   value="0" />
                <index_type name="Ethernet"     value="2" />
            </enum_index>

            <enum_index name="ib_sel" reg="">
                <index_type name="IB0"          value="0" />
                <index_type name="IB1"          value="1" />
                <index_type name="IB2"          value="2" />
                <index_type name="IB3"          value="3" />
            </enum_index>

            <enum_index name="unit" reg="">
                <index_type name="DLN"          value="0" />
                <index_type name="CLN"          value="1" />
            </enum_index>
            
            <index_set idx1_name="port_type" idx2_name="lane" reg1="" reg2="">
                <index_set_values idx1="0" idx2="0"/>
                <index_set_values idx1="0" idx2="1"/>
                <index_set_values idx1="0" idx2="2"/>
                <index_set_values idx1="0" idx2="3"/>
                <index_set_values idx1="0" idx2="4"/>
                <index_set_values idx1="0" idx2="5"/>
                <index_set_values idx1="0" idx2="6"/>
                <index_set_values idx1="0" idx2="7"/>
            </index_set>

            <index_set idx1_name="port_type" idx2_name="grp" reg1="" reg2="">
                <index_set_values idx1="0" idx2="0x6"/>
                <index_set_values idx1="0" idx2="0x12"/>
                <index_set_values idx1="0" idx2="0x16"/>
                <index_set_values idx1="0" idx2="0x23"/>
                <index_set_values idx1="1" idx2="0x16"/>
                <index_set_values idx1="2" idx2="0x16"/>
                <index_set_values idx1="3" idx2="0x16"/>
                <index_set_values idx1="4" idx2="0x12"/>
                <index_set_values idx1="5" idx2="0x12"/>
                <index_set_values idx1="5" idx2="0x16"/>
            </index_set>

        </indexes>

        <tree>
            <hidden_index name="pnat" value="0"/>
            <hidden_index name="swid" value="0"/>
            <hidden_index name="prio_tc" value="0"/>
            <hidden_index name="grp_profile" value="0"/>
            <hidden_index name="test_mode" value="0"/>
            <hidden_index name="hist_type" value="0"/>
            <hidden_index name="ig" value="0"/>
            <hidden_index name="asic_index" value="0"/>
            <hidden_index name="enum_init" value="0"/>
            <hidden_index name="db_index" value="0"/>
            <hidden_index name="db" value="0"/>
            <reg name="MSGI"/>
            <reg name="MGIR"/>
            <reg name="MDIR"/>
            <reg name="SPAD"/>
            <seq_index name="pll_group" min="1" max="10" system="true">
                <reg name="PPLL"/>
            </seq_index>
            <seq_index name="local_port" min="1" max="128" system="true">
                <reg name="PMDR"/>
                <reg name="PPHCR"/>
                <enum_index name="port_type" reg="">
                    <seq_index name="lane" min="0" max="7">
                        <dynamic_tree type="system">
                            <enum_index name="ib_sel" reg="">
                                <reg name="SLRIP"/>
                            </enum_index>
                            <reg name="SLRIP"/>
                        </dynamic_tree>
                        <dynamic_tree type="system">
                            <seq_index name="fom_measurment" min="0" max="15">
                                <reg name="SLRG"/>
                            </seq_index>
                            <reg name="SLRG"/>
                        </dynamic_tree>
                        <reg name="SLRP"/>
                        <reg name="SLTP"/>
                        <reg name="SLLM"/>
                    </seq_index>
                    <enum_index name="grp" reg="">
                        <reg name="PPCNT"/>
                    </enum_index>
                    <enum_index name="proto_mask" reg="">
                        <reg name="PTYS"/>
                    </enum_index>
                    <enum_index name="page_select" reg="">
                        <reg name="PDDR"/>
                    </enum_index>
                </enum_index>
                <dynamic_tree type="system">
                    <seq_index name="lane" min="0" max="7">
                        <enum_index name="unit" reg="">
                            <reg name="PEUCG"/>
                        </enum_index>
                    </seq_index>
                </dynamic_tree>
            </seq_index>
            <enum_index name="slot_index" reg="">
                <reg name="MVCAP"/>
                <reg name="MTCAP"/>
                <seq_index name="i" min="0" max="0">
                    <seq_index name="sensor_index" min="0" max="1" system="true">
                        <reg name="MTMP"/>
                    </seq_index>
                    <seq_index name="sensor_index" min="64" max="127">
                        <reg name="MTMP"/>
                    </seq_index>
                    <seq_index name="sensor_index" min="256" max="263">
                        <reg name="MTMP"/>
                    </seq_index>
                </seq_index>
                <seq_index name="i" min="1" max="1">
                    <seq_index name="sensor_index" min="1" max="150">
                        <reg name="MTMP"/>
                    </seq_index>
                </seq_index>
            </enum_index>
        </tree>
    </protocol>

    <protocol name="ib">
        <indexes>
            <enum_index name="port_type" reg="">
                <index_type name="Network"   value="0" />
                <index_type name="Near_end_point"   value="1" />
                <index_type name="Internal_RC_LR"   value="2" />
                <index_type name="Far_end"   value="3" />
                <index_type name="USR_main"   value="4" />
                <index_type name="USR_tile"   value="5" />
            </enum_index>

            <enum_index name="grp" reg="">
                <index_type name="IEEE_802_3"   value="0x0" />
                <index_type name="RFC_2863"   value="0x1" />
                <index_type name="RFC_2819"   value="0x2" />
                <index_type name="RFC_3635"   value="0x3" />
                <index_type name="Ethernet_Extended"   value="0x5" />
                <index_type name="Ethernet_Discard"   value="0x6" />
                <index_type name="Link_Level_Retransmission"   value="0x8" />
                <index_type name="Per_Priority"   value="0x10" />
                <index_type name="Per_Traffic_Class"   value="0x11" />
                <index_type name="Physical_layer"   value="0x12" />
                <index_type name="Per_Traffic_Class_Congestion"   value="0x13" />
                <index_type name="Per_Receive_Buffer"   value="0x15" />
                <index_type name="Physical_Layer_Statistical"   value="0x16" />
                <index_type name="Out_of_Band_Port"   value="0x19" />
                <index_type name="InfiniBand_Port"   value="0x20" />
                <index_type name="InfiniBand_Extended_Port"   value="0x21" />
                <index_type name="PLR_counters_group"   value="0x22" />
                <index_type name="RS_FEC_Histogram_group"   value="0x23" />
                <index_type name="USR_XSR_Physical_layer_counters_group"   value="0x24" />
                <index_type name="Infiniband_pkts_counters"   value="0x25" />
            </enum_index>

            <enum_index name="page_select" reg="">
                <index_type name="Operational_info_page"         value="0" />
                <index_type name="Troubleshooting_info_page"     value="1" />
                <index_type name="Phy_info_page"                 value="2" />
                <index_type name="Module_info_page"              value="3" />
                <index_type name="Port_events_page"              value="4" />
                <index_type name="Device_events_page"            value="5" />
                <index_type name="Link_down_info"                value="6" />
                <index_type name="Link_down_events"              value="7" />
                <index_type name="Link_up_info"                  value="8" />
                <index_type name="Module_latched_flag_info_page" value="9" />
                <index_type name="link_down_info_ext"            value="10" />
                <index_type name="mng_debug_page"                value="0xFE" />
                <index_type name="phy_debug_page"                value="0XFF" />
            </enum_index>

            <enum_index name="slot_index" reg="">
                <index_type name="Main_board"		value="0" />
            </enum_index>

            <enum_index name="proto_mask" reg="">
                <index_type name="InfiniBand"	value="0" />
                <index_type name="Ethernet"     value="2" />
            </enum_index>
            
             <enum_index name="ib_sel" reg="">
                <index_type name="IB0"          value="0" />
                <index_type name="IB1"          value="1" />
                <index_type name="IB2"          value="2" />
                <index_type name="IB3"          value="3" />
            </enum_index>

            <enum_index name="unit" reg="">
                <index_type name="DLN"          value="0" />
                <index_type name="CLN"          value="1" />
            </enum_index>
            
            <index_set idx1_name="port_type" idx2_name="lane" reg1="" reg2="">
                <index_set_values idx1="0" idx2="0"/>
                <index_set_values idx1="0" idx2="1"/>
                <index_set_values idx1="0" idx2="2"/>
                <index_set_values idx1="0" idx2="3"/>
                <index_set_values idx1="0" idx2="4"/>
                <index_set_values idx1="0" idx2="5"/>
                <index_set_values idx1="0" idx2="6"/>
                <index_set_values idx1="0" idx2="7"/>
            </index_set>

            <index_set idx1_name="port_type" idx2_name="grp" reg1="" reg2="">
                <index_set_values idx1="0" idx2="0x12"/>
                <index_set_values idx1="0" idx2="0x16"/>
                <index_set_values idx1="0" idx2="0x20"/>
                <index_set_values idx1="0" idx2="0x21"/>
                <index_set_values idx1="0" idx2="0x23"/>
                <index_set_values idx1="0" idx2="0x25"/>
                <index_set_values idx1="1" idx2="0x16"/>
                <index_set_values idx1="2" idx2="0x16"/>
                <index_set_values idx1="3" idx2="0x16"/>
                <index_set_values idx1="4" idx2="0x12"/>
                <index_set_values idx1="5" idx2="0x12"/>
                <index_set_values idx1="5" idx2="0x16"/>
            </index_set>
            
        </indexes>

        <tree>
            <hidden_index name="pnat" value="0"/>
            <hidden_index name="swid" value="0"/>
            <hidden_index name="prio_tc" value="0"/>
            <hidden_index name="grp_profile" value="0"/>
            <hidden_index name="ig" value="0"/>
            <hidden_index name="asic_index" value="0"/>
            <hidden_index name="hist_type" value="0"/>
            <hidden_index name="enum_init" value="0"/>
            <hidden_index name="db_index" value="0"/>
            <hidden_index name="db" value="0"/>
            <reg name="MSGI"/>
            <reg name="MGIR"/>
            <reg name="MDIR"/>
            <seq_index name="router_entity" min="0" max="1" system="false">
                <reg name="SPZR"/>
            </seq_index>
            <seq_index name="pll_group" min="1" max="10" system="true">
                <reg name="PPLL"/>
            </seq_index>
            <seq_index name="local_port" min="1" max="128" system="true">
                <reg name="PMDR"/>
                <reg name="PPHCR"/>
                <enum_index name="port_type" reg="">
                    <seq_index name="lane" min="0" max="7">
                        <dynamic_tree type="system">
                            <enum_index name="ib_sel" reg="">
                                <reg name="SLRIP"/>
                            </enum_index>
                            <reg name="SLRIP"/>
                        </dynamic_tree>
                        <dynamic_tree type="system">
                            <seq_index name="fom_measurment" min="0" max="15">
                                <reg name="SLRG"/>
                            </seq_index>
                            <reg name="SLRG"/>
                        </dynamic_tree>
                        <reg name="SLRP"/>
                        <reg name="SLTP"/>
                        <reg name="SLLM"/>
                    </seq_index>
                    <enum_index name="grp" reg="">
                        <reg name="PPCNT"/>
                    </enum_index>
                    <enum_index name="proto_mask" reg="">
                        <reg name="PTYS"/>
                    </enum_index>
                    <enum_index name="page_select" reg="">
                        <reg name="PDDR"/>
                    </enum_index>
                </enum_index>
                <dynamic_tree type="system">
                    <seq_index name="lane" min="0" max="7">
                        <enum_index name="unit" reg="">
                            <reg name="PEUCG"/>
                        </enum_index>
                    </seq_index>
                </dynamic_tree>
            </seq_index>
            <enum_index name="slot_index" reg="">
                <reg name="MVCAP"/>
                <reg name="MTCAP"/>
                <seq_index name="i" min="0" max="0">
                    <seq_index name="sensor_index" min="0" max="1" system="true">
                        <reg name="MTMP"/>
                    </seq_index>
                    <seq_index name="sensor_index" min="64" max="127">
                        <reg name="MTMP"/>
                    </seq_index>
                    <seq_index name="sensor_index" min="256" max="263">
                        <reg name="MTMP"/>
                    </seq_index>
                </seq_index>
                <seq_index name="i" min="1" max="1">
                    <seq_index name="sensor_index" min="1" max="150">
                        <reg name="MTMP"/>
                    </seq_index>
                </seq_index>
            </enum_index>
        </tree>
    </protocol>
</app>
